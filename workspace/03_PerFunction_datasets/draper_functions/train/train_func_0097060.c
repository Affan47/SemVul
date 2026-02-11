discard() {
  if (!(flags&ConnectionClose) && !(flags&HeadRequest)) {
    FXchar buffer[1024];
    while(readBody(buffer,1024)==1024) ;
    }
  }
