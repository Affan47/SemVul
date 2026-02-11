extension(const FXString& file){
  register FXint f,e,i,n;
  if(!file.empty()){
    n=0;
#ifdef WIN32
    if(Ascii::isLetter(file[0]) && file[1]==':') n=2;
#endif
    f=n;
    while(file[n]){
      if(ISPATHSEP(file[n])) f=n+1;
      n++;
      }
    if(file[f]=='.') f++;
    e=i=n;
    while(f<i){
      if(file[--i]=='.'){ e=i+1; break; }
      }
    return FXString(file.text()+e,n-e);
    }
  return FXString::null;
  }
