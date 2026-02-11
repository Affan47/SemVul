ChanWrite (Tcl_Interp *interp, CONST char *fileName, Tcl_Obj *format, Tk_PhotoImageBlock *blockPtr) {

  int Type = CXIMAGE_FORMAT_UNKNOWN;
  char * cxFormat = NULL;
  Tcl_Obj *data = NULL;
  Tcl_Channel chan = Tcl_OpenFileChannel(interp, fileName, "w", 0644);

  if (chan == NULL)
    return TCL_ERROR;

  if (format) {
    cxFormat = Tcl_GetStringFromObj(format, NULL);
    Type = GetFileTypeFromFormat(cxFormat);
  }

  if (Type == CXIMAGE_FORMAT_UNKNOWN) {
    Type = GetFileTypeFromFileName((char *) fileName);
  }

  if (Type == CXIMAGE_FORMAT_UNKNOWN) {
    Type = CXIMAGE_FORMAT_GIF;
  }


  if (DataWrite(interp, Type, blockPtr) == TCL_ERROR) {
    return TCL_ERROR;
  }

  data = Tcl_GetObjResult(interp);

  Tcl_SetChannelOption(interp, chan, "-encoding", "binary");
  Tcl_SetChannelOption(interp, chan, "-translation", "binary");

  Tcl_WriteObj(chan, data);

  Tcl_ResetResult(interp);

  return Tcl_Close(interp, chan);
}
