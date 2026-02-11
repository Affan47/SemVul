read_body(FXchar *& body) {
  body=NULL;

  if (content_length>0) {
    allocElms(body,content_length);
    FXival n = read(body,content_length);
    if (n!=content_length) {
      freeElms(body);
      body=NULL;
      return -1;
      }
    return content_length;
    }
  else if (content_length<0) {
    const FXint BLOCK=4096;
    FXint  size = 0;
    FXival len  = 0;
    FXival n;
    do {
      resizeElms(body,size+BLOCK);
      size+=BLOCK;
      n = read(body+len,BLOCK);
      if (n>0) len+=n;
      }
    while(n==BLOCK);
    return len;
    }
  else {
    return 0;
    }
  }
