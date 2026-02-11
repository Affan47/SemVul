settimeout(const char *arg) {
  char *ep;
  timeout= strtoul(arg,&ep,0);
  if (*ep) usageerr("invalid timeout");
}
