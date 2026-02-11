GetHexByte(FILE *f) {
  for (;;) {
    char a[3];
    if ((a[0] = fgetc(f)) == EOF)
      break;
    if ((a[0] >= '0' && a[0] <= '9') ||
	(a[0] >= 'a' && a[0] <= 'f') ||
	(a[0] >= 'A' && a[0] <= 'F')) {
      if ((a[1] = fgetc(f)) == EOF)
	break;
      a[2] = '\0';
      return strtol(a,NULL,16);
    }
  }
  return EOF;
}
