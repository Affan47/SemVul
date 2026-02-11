ObjMatch (Tcl_Obj *data, Tcl_Obj *format, int *widthPtr, int *heightPtr, Tcl_Interp *interp) {

  BYTE * buffer = NULL;
  int length = 0;

  CxImage image;

  LOG("Data matching");

  buffer = Tcl_GetByteArrayFromObj(data, &length);

  if (image.CheckFormat(buffer,length,CXIMAGE_FORMAT_UNKNOWN)) {
    LOG("Supported Format : ");
    APPENDLOG(image.GetType());
    LOG("Size : ");
    *widthPtr = image.GetWidth();
    *heightPtr = image.GetHeight();
    APPENDLOG(*widthPtr);
    APPENDLOG("x");
    APPENDLOG(*heightPtr);
    return true;
  }

  LOG("Unknown format");
  return false;
}
