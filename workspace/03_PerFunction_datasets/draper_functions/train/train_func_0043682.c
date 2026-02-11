put_in_buffer(int len) {
  if (value_ == buffer && bufsize > len) {
    buffer[size_] = 0;
    return;
  }
  if (!bufsize) {
    if (len > size_) len += 9;
    bufsize = len+1;
    buffer = (char*)malloc(bufsize);
  } else if (bufsize <= len) {

    int moveit = (value_ >= buffer && value_ < buffer+bufsize);

    if (len > size_) {
      do {bufsize *= 2;} while (bufsize <= len);
    } else {
      bufsize = len+1;
    }


    char* nbuffer = (char*)realloc(buffer, bufsize);
    if (moveit) value_ += (nbuffer-buffer);
    buffer = nbuffer;
  }
  memmove(buffer, value_, size_); buffer[size_] = 0;
  value_ = buffer;
}
