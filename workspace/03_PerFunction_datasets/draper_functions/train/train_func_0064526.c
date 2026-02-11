dequote(FXchar* text) const {
  register FXchar *result=text;
  register FXchar *ptr=text;
  register FXuint v;
  if(*text=='"'){
    text++;
    while((v=*text++)!='\0' && v!='\n' && v!='"'){
      if(v=='\\'){
        v=*text++;
        switch(v){
          case 'n':
            v='\n';
            break;
          case 'r':
            v='\r';
            break;
          case 'b':
            v='\b';
            break;
          case 'v':
            v='\v';
            break;
          case 'a':
            v='\a';
            break;
          case 'f':
            v='\f';
            break;
          case 't':
            v='\t';
            break;
          case '\\':
            v='\\';
            break;
          case '"':
            v='"';
            break;
          case '\'':
            v='\'';
            break;
          case 'x':
            v='x';
            if(Ascii::isHexDigit(*text)){
              v=Ascii::digitValue(*text++);
              if(Ascii::isHexDigit(*text)){
                v=(v<<4)+Ascii::digitValue(*text++);
                }
              }
            break;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
            v=v-'0';
            if('0'<=*text && *text<='7'){
              v=(v<<3)+*text++-'0';
              if('0'<=*text && *text<='7'){
                v=(v<<3)+*text++-'0';
                }
              }
            break;
          }
        }
      *ptr++=v;
      }
    *ptr='\0';
    }
  return result;
  }
