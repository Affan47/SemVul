erase(FXint pos){
  register FXint len=length();
  if(0<=pos && pos<len){
    memmove(str+pos,str+pos+1,len-pos-1);
    length(len-1);
    }
  return *this;
  }
