whois_get_type(char *type)
{
  int cnt = 0, retval = -1;
  char buffer[WHOISCMDLEN];
  signed char c;

  read(opt.whois_sock, &c, 1);
  while ((c != '\n') && (c != EOF) && (cnt < WHOISCMDLEN)) {
    buffer[cnt] = c;
    cnt++;
    read(opt.whois_sock, &c, 1);
  }
  buffer[cnt] = '\0';

  switch (buffer[0]) {
  case 'A':
    *type = buffer[0];
    retval = atoi(&buffer[1]);
    break;
  case 'C':
    *type = buffer[0];
    retval = 0;
    break;
  default:
    *type = '\0';
  }

  return (retval);
}
