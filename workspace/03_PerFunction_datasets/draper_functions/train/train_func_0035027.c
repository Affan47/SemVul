errmsg_puts(int fd,const char* s) {
  x[l].iov_base=(char*)s;
  x[l].iov_len=str_len(s);
  if (++l==COUNT) errmsg_flush(fd);
}
