extensionFromPattern(const FXString& pattern){
  FXint beg,end,c;
  beg=0;
  if(pattern[beg]=='*'){
    beg++;
    if(pattern[beg]=='.'){
      beg++;
      end=beg;
      while((c=pattern[end])!='\0' && c!=',' && c!='|'){
        if(c=='*' || c=='?' || c=='[' || c==']' || c=='^' || c=='!') return FXString::null;
        end++;
        }
      return pattern.mid(beg,end-beg);
      }
    }
  return FXString::null;
  }
