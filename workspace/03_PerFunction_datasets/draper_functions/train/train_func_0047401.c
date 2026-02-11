StringWrite (Tcl_Interp *interp, Tcl_Obj *format, Tk_PhotoImageBlock *blockPtr) {

  int Type = CXIMAGE_FORMAT_UNKNOWN;
  char * cxFormat = NULL;

  if (format) {
    cxFormat = Tcl_GetStringFromObj(format, NULL);
    Type = GetFileTypeFromFormat(cxFormat);
  }

  if (Type == CXIMAGE_FORMAT_UNKNOWN) {
    Type = CXIMAGE_FORMAT_GIF;
  }

  return DataWrite(interp, Type, blockPtr);

}
