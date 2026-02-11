startup(void) {
  int r;

  if (nonblock(0,1)) sysfail("set stdin to nonblocking mode");
  if (nonblock(1,1)) sysfail("set stdout to nonblocking mode");
  memset(&sa,0,sizeof(sa));
  sa.sin_family= AF_INET;
  if (config_text) {
    r= adns_init_strcfg(&ads,initflags,stderr,config_text);
  } else {
    r= adns_init(&ads,initflags,0);
  }
  if (r) adnsfail("init",r);
  cbyte= -1;
  inbyte= -1;
  inbuf= 0;
  if (!bracket) startaddr();
}
