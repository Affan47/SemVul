dcc_relay(int idx, char *buf, int j)
{
  unsigned char *p = (unsigned char *) buf;
  int mark;

  for (j = 0; dcc[j].sock != dcc[idx].u.relay->sock ||
       dcc[j].type != &DCC_RELAYING; j++);


  if (!(dcc[j].status & STAT_TELNET)) {
    while (*p != 0) {
      while (*p != 255 && (*p != '\033' || *(p + 1) != '[') && *p != '\r' && *p)
        p++;
      if (*p == 255) {
        mark = 2;
        if (!*(p + 1))
          mark = 1;
        if ((*(p + 1) >= 251) || (*(p + 1) <= 254)) {
          mark = 3;
          if (!*(p + 2))
            mark = 2;
        }
        strcpy((char *) p, (char *) (p + mark));
      } else if (*p == '\033') {
        unsigned char *e;


        for (e = p + 2; *e != 'm' && *e; e++);
        strcpy((char *) p, (char *) (e + 1));
      } else if (*p == '\r')
        strcpy((char *) p, (char *) (p + 1));
    }
    if (!buf[0])
      dprintf(-dcc[idx].u.relay->sock, " \n");
    else
      dprintf(-dcc[idx].u.relay->sock, "%s\n", buf);
    return;
  }

  if (!buf[0])
    dprintf(-dcc[idx].u.relay->sock, " \r\n");
  else
    dprintf(-dcc[idx].u.relay->sock, "%s\r\n", buf);
}
