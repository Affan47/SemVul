position(FXlong offset,FXWhence whence){
  if(dir==FXStreamDead){fxerror("FXStream::position: stream is not open.\n");}
  if(code==FXStreamOK){
    if(whence==FXFromCurrent) offset=offset+pos;
    else if(whence==FXFromEnd) offset=offset+endptr-begptr;
    pos=offset;
    return true;
    }
  return false;
  }
