escape(const FXString& s){
  register FXint p=0;
  register FXint c;
  FXString result;
  while(p<s.length()){
    c=s[p++];
    switch(c){
      case '\n':
        result.append("\\n");
        break;
      case '\r':
        result.append("\\r");
        break;
      case '\b':
        result.append("\\b");
        break;
      case '\v':
        result.append("\\v");
        break;
      case '\a':
        result.append("\\a");
        break;
      case '\f':
        result.append("\\f");
        break;
      case '\t':
        result.append("\\t");
        break;
      case '\\':
        result.append("\\\\");
        break;
      case '"':
        result.append("\\\"");
        break;
      case '\'':
        result.append("\\\'");
        break;
      default:
        if(0x20<=c && c<=0x7F){
          result.append(c);
          }
        else{
          result.append("\\x");
          result.append(FXString::HEX[(c>>4)&15]);
          result.append(FXString::HEX[c&15]);
          }
        break;
      }
    }
  return result;
  }
