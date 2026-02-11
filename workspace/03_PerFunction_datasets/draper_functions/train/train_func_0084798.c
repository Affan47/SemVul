read_line (int s, char *dest)
{
  int length;
  int offset=0;
  char buffer[GSERV_BUFSZ+1];

  while ((length=read(s,buffer+offset,1)>0) && buffer[offset]!='\n'
	 && buffer[offset] != EOT_CHR) {
    offset += length;
    if (offset >= GSERV_BUFSZ)
      break;
  }
  buffer[offset] = '\0';
  strcpy(dest,buffer);
  return 1;
}
