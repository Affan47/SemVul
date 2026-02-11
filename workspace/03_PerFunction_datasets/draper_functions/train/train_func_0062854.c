nextLine(FXint pos,FXint nl) const {
  FXASSERT(0<=pos && pos<=length);
  if(nl<=0) return pos;
  while(pos<length){
    if(getByte(pos)=='\n' && --nl==0) return pos+1;
    pos++;
    }
  return length;
  }
