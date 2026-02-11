isdelimiter(const FXchar *delimiters,FXwchar w){
  return w<128 && strchr(delimiters,w);
  }
