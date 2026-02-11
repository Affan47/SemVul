OpenZipInternal(void *z,unsigned int len,DWORD flags, const char *password)
{ TUnzip *unz = new TUnzip(password);
  lasterrorU = unz->Open(z,len,flags);
  if (lasterrorU!=ZR_OK) {delete unz; return 0;}
  TUnzipHandleData *han = new TUnzipHandleData;
  han->flag=1; han->unz=unz; return (HZIP)han;
}
