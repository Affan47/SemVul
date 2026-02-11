find(const FXchar* substr,FXint n,FXint pos) const {
  register FXint len=length();
  if(0<=pos && 0<n && n<=len){
    register FXint c=substr[0];
    len=len-n+1;
    while(pos<len){
      if(str[pos]==c){
        if(!compare(str+pos,substr,n)){
          return pos;
          }
        }
      pos++;
      }
    }
  return -1;
  }
