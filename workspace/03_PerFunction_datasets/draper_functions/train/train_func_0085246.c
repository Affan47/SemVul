open(FXStreamDirection save_or_load,FXuchar* data){
  if(save_or_load!=FXStreamSave && save_or_load!=FXStreamLoad){fxerror("FXMemoryStream::open: illegal stream direction.\n");}
  if(FXStream::open(save_or_load,data?ULONG_MAX:16UL,data)){
    if(save_or_load==FXStreamSave){
      wrptr=begptr;
      rdptr=begptr;
      }
    else{
      wrptr=endptr;
      rdptr=begptr;
      }
    return true;
    }
  return false;
  }
