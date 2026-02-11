onClipboardRequest(FXObject* sender,FXSelector sel,void* ptr){
  FXEvent *event=(FXEvent*)ptr;


  if(FXScrollArea::onClipboardRequest(sender,sel,ptr)) return 1;


  if(event->target==csvType || event->target==stringType || event->target==textType || event->target==utf8Type || event->target==utf16Type){
    FXString string=clipped;


#ifdef WIN32
    unixToDos(string);
#endif


    if(event->target==csvType){
      FXTRACE((100,"Request CSV\n"));
      string.substitute('\t',',',true);
      setDNDData(FROM_CLIPBOARD,event->target,string);
      return 1;
      }


    if(event->target==utf8Type){
      FXTRACE((100,"Request UTF8\n"));
      setDNDData(FROM_CLIPBOARD,event->target,string);
      return 1;
      }


    if(event->target==stringType || event->target==textType){
      FX88591Codec ascii;
      FXTRACE((100,"Request ASCII\n"));
      setDNDData(FROM_CLIPBOARD,event->target,ascii.utf2mb(clipped));
      return 1;
      }


    if(event->target==utf16Type){
      FXUTF16LECodec unicode;
      FXTRACE((100,"Request UTF16\n"));
      setDNDData(FROM_CLIPBOARD,event->target,unicode.utf2mb(clipped));
      return 1;
      }
    }
  return 0;
  }
