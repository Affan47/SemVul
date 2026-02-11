socket_readline(CONN *C, char *ptr, size_t maxlen)
{
  int type;
  int n, len, res;
  char c;

  len = maxlen;
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &type);

  for (n = 1; n < len; n ++) {
    if ((res = socket_read(C, &c, 1)) == 1) {
      *ptr++ = c;
      if (c=='\n') break;
    }
    else if (res == 0) {
      if (n == 1)
        return 0;
      else
        break;
    } else {
      return -1;
    }
  }

  *ptr=0;

  pthread_setcanceltype(type,NULL);
  pthread_testcancel();

  return n;
}
