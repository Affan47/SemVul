assign(const FXchar* s){
  if(s && s[0]){
    register FXint n=strlen(s);
    length(n);
    memmove(str,s,n);
    }
  else{
    length(0);
    }
  return *this;
  }
