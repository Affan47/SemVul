extractText(FXchar *text,FXint pos,FXint n) const {
  if(n<0 || pos<0 || length<pos+n){ fxerror("%s::extractText: bad argument.\n",getClassName()); }
  FXASSERT(0<=n && 0<=pos && pos+n<=length);
  if(pos+n<=gapstart){
    memcpy(text,&buffer[pos],n);
    }
  else if(pos>=gapstart){
    memcpy(text,&buffer[pos-gapstart+gapend],n);
    }
  else{
    memcpy(text,&buffer[pos],gapstart-pos);
    memcpy(&text[gapstart-pos],&buffer[gapend],pos+n-gapstart);
    }
  }
