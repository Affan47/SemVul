onClipboardRequest(FXObject* sender,FXSelector sel,void* ptr){
  FXEvent *event=(FXEvent*)ptr;
  FXuchar *cbdata;
  FXDragType types[]={utf8Type,stringType,0};


  if(FXScrollArea::onClipboardRequest(sender,sel,ptr)) return 1;

  for (FXDragType *dt=InUTF8Mode(_scint)?types:types+1; *dt; dt++) {
    if(event->target==*dt){

      size_t len=_scint->copyText.len;
      if (!_scint->copyText.rectangular) {len--;}
      FXCALLOC(&cbdata,FXuchar,len+1);
      memcpy(cbdata,_scint->copyText.s,len);
  #ifndef WIN32
      setDNDData(FROM_CLIPBOARD,*dt,cbdata,len);
  #else
      setDNDData(FROM_CLIPBOARD,*dt,cbdata,len+1);
  #endif

      return 1;
    }
  }
  return 0;
}
