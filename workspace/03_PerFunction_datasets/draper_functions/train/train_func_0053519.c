read_header(FXString & header,FXuint mode) {
  while(!parse_header(header,mode)) {
    if (fill()==-1)
      return false;
    }
  return true;
  }
