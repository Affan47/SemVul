_mkStringFromFortran(char* fstring, size_t length) {


    fstring[length] = '\0';
    for (size_t i = length-1; i >= 0; --i) {

      if (fstring[i] != ' ') break;

      fstring[i] = '\0';
    }
    return string(fstring);
  }
