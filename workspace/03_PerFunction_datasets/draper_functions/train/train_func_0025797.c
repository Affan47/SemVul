insert(FXint pos,const FXwchar* s,FXint m){
  if(s && 0<m){
    register FXint len=length();
    register FXint n=utfslen(s,m);
    length(len+n);
    if(pos<=0){
      memmove(str+n,str,len);
      wc2utfs(str,s,m);
      }
    else if(pos>=len){
      wc2utfs(str+len,s,m);
      }
    else{
      memmove(str+pos+n,str+pos,len-pos);
      wc2utfs(str+pos,s,m);
      }
    }
  return *this;
  }
