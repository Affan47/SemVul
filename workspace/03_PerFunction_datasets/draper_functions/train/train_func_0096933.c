Tk_DisableAnimation (ClientData clientData,
		       Tcl_Interp *interp,
		       int objc,
		       Tcl_Obj *CONST objv[])
{
	CxImage image;
	char *ImageName = NULL;
	Tk_PhotoHandle Photo;
	GifInfo* item = NULL;

	if( objc != 2) {
		Tcl_AppendResult (interp, "Wrong number of args.\nShould be \"::CxImage::StopAnimation photoImage_name\"" , (char *) NULL);
		return TCL_ERROR;
	}


	ImageName = Tcl_GetStringFromObj(objv[1], NULL);
	if ( (Photo = Tk_FindPhoto(interp, ImageName)) == NULL) {
		Tcl_AppendResult(interp, "The image you specified is not a valid photo image", NULL);
		return TCL_ERROR;
	}
	item = TkCxImage_lstGetItem(Photo);
	if (item != NULL && item->Enabled) {
		item->Enabled=false;
		if (item->timerToken != NULL) {
			Tcl_DeleteTimerHandler(item->timerToken);
			item->timerToken = NULL;
		}
	}
	return TCL_OK;
}
