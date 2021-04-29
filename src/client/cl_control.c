/*
sswolf - req SS functions. 
Source: Nate (rtcwMP)
*/

#include "client.h"
#include "http.h"


/*
================
Takes ScreenShot
================
*/
//void CL_takeSS(char* name, int quality) {
void CL_takeSS(char* name) {

	//Cbuf_ExecuteText(EXEC_NOW, va("screenshotJPEG sys %s %d\n", name, quality));
	Cbuf_ExecuteText(EXEC_NOW, va("screenshotJPEG %s\n", name));
}

/*
================
Generate time..
================
*/
void CL_actionGenerateTime(void) {

	int min = 600 * 1000;	// 10 mins
	int max = 12000 * 1000;	// 20 mins
	int time = rand() % max + min;

	cl.clientSSAction = cl.serverTime + time;
}

/*
================
Check if it's time to take the screenshot..
================
*/
void CL_checkSSTime(void) {

	if (!cl.clientSSAction) 
	{
		CL_actionGenerateTime();
	}
	else 
	{
		if (cl.serverTime >= cl.clientSSAction) 
		{
			//CL_RequestedSS(45);
			CL_RequestedSS();
		}
	}
}

/*
================
ScreenShot request from server
================
*/
//void CL_RequestedSS(int quality) {
void CL_RequestedSS() {
	char* filename = va("screenshots/%d", cl.clientSSAction);

	//CL_takeSS(filename, quality);
	CL_takeSS(filename);
	CL_actionGenerateTime();

	// Try once more if it fails..
	/*if (!CL_HTTP_SSUpload(WEB_SS_UPLOAD, filename, Cvar_VariableString("cl_guid")))
		CL_HTTP_SSUpload(WEB_SS_UPLOAD, filename, Cvar_VariableString("cl_guid"));*/
}

