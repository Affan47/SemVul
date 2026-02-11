stripHotKey(const FXString& string){
  FXString result=string;
  register FXint len=result.length();
  register FXint i,j;
  for(i=j=0; j<len; j++){
    if(result[j]=='&'){
      if(result[j+1]!='&') continue;
      j++;
      }
    result[i++]=result[j];
    }
  result.trunc(i);
  return result;
  }
