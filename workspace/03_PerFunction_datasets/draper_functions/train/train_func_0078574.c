varinit(const char *fmt, va_list args) {
  size_t bufsize, msglen;


  bufsize = 3*strlen(fmt)/2;
  msg = new char[bufsize];
  if (!msg) out_of_memory();
  msglen=vsnprintf(msg, bufsize, fmt, args);


  if (msglen+1 > bufsize) {
    bufsize = msglen+1;
    delete msg;
    msg = new char[bufsize];
    if (!msg) out_of_memory();

    vsnprintf(msg, bufsize, fmt, args);
  }
}
