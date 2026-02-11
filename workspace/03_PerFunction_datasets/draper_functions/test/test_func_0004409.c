position(FXlong offset,FXWhence whence){
  register FXlong p;
  if(dir==FXStreamDead){ fxerror("FXMemoryStream::position: stream is not open.\n"); }
  if(code==FXStreamOK){
    FXASSERT(FXFromStart==SEEK_SET);
    FXASSERT(FXFromCurrent==SEEK_CUR);
    FXASSERT(FXFromEnd==SEEK_END);
    if(dir==FXStreamSave){


      writeBuffer(0);


      if(whence==FXFromCurrent) offset+=wrptr-rdptr;


      if((p=file.position(offset,whence))<0){
        code=FXStreamFull;
        return FALSE;
        }


      wrptr=begptr;
      rdptr=begptr;
      }
    else{


      if(whence==FXFromCurrent) offset-=wrptr-rdptr;


      if((p=file.position(offset,whence))<0){
        code=FXStreamEnd;
        return false;
        }


      wrptr=begptr;
      rdptr=begptr;
      }
    pos=p;
    return true;
    }
  return false;
  }
