LoadFromFile(Tcl_Interp * interp, CxImage * image, char * fileName, int Type) {

  Tcl_Obj *data = Tcl_NewObj();
  Tcl_Channel chan = Tcl_OpenFileChannel(interp, fileName, "r", 0);
  BYTE * FileData = NULL;
  int length = 0;
  int retVal;

  if (chan == NULL)
    return FALSE;


  if (Type == CXIMAGE_FORMAT_UNKNOWN) {
    Type = GetFileTypeFromFileName((char *)fileName);
  }

  if (Type == CXIMAGE_FORMAT_UNKNOWN) {
    Type = CXIMAGE_FORMAT_GIF;
  }

  Tcl_SetChannelOption(interp, chan, "-encoding", "binary");
  Tcl_SetChannelOption(interp, chan, "-translation", "binary");

  Tcl_ReadChars(chan, data, -1, 0);

  Tcl_Close(interp, chan);

  FileData = Tcl_GetByteArrayFromObj(data, &length);


  if (! image->Decode(FileData, length, Type) &&
      ! image->Decode(FileData, length, CXIMAGE_FORMAT_GIF) &&
      ! image->Decode(FileData, length, CXIMAGE_FORMAT_PNG) &&
      ! image->Decode(FileData, length, CXIMAGE_FORMAT_JPG) &&
      ! image->Decode(FileData, length, CXIMAGE_FORMAT_TGA) &&
      ! image->Decode(FileData, length, CXIMAGE_FORMAT_BMP))
    retVal = FALSE;
  else
    retVal = TRUE;

  Tcl_DecrRefCount(data);
  return retVal;

}
