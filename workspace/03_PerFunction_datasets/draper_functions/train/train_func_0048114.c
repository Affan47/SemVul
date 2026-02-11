ftp_pasv(CONN *C)
{
  int  i, code;
  char *ptr;
  unsigned char addr[6];

  code = __request(C, "PASV");
  if (!okay(code)) return FALSE;

  ptr = (char *) C->chkbuf;
  for (ptr += 4; *ptr && !isdigit(*ptr); ptr++);

  if (!*ptr) return FALSE;

  for (i = 0; i < 6; i++) {
    addr[i] = 0;
    for (; isdigit(*ptr); ptr++)
      addr[i] = (*ptr - '0') + 10 * addr[i];

    if (*ptr == ',') ptr++;
    else if (i < 5)  return FALSE;
  }
  snprintf(C->ftp.host, sizeof(C->ftp.host), "%d.%d.%d.%d", addr[0],addr[1],addr[2],addr[3]);
  C->ftp.port = (addr[4] << 8) + addr[5];

  return TRUE;
}
