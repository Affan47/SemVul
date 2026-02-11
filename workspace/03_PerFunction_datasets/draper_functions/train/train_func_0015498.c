strings(FILE *pf) {
  static char printme[1024];
  int sz;
  unsigned char *cdata;
  int nread;
  int printmeindex;
  cdata = filebuf(pf,&sz);
  nread = fread(cdata, 1, sz, pf);
  printmeindex = 0;
  if (nread > 0) {
    int i;
    unsigned char c;
    int isprintable;
    int iseol;
    for (i = 0; i < nread; i++) {
      c = cdata[i];
      isprintable = isprint(c);
      iseol = 0;
      if (c == 0 || c == '\n' || printmeindex >= sizeof(printme)-1) iseol = 1;
      if (iseol || !isprintable) {
	if (printmeindex > 3 && iseol) {
	  printme[printmeindex++] = 0;
	  printf("%s\n", printme);
	  printmeindex = 0;
	}
      }
      else if (isprintable) {
	printme[printmeindex++] = c;
      }
    }
  }
  if (printmeindex > 3) {
    printme[printmeindex++] = 0;
    printf("%s\n", printme);
    printmeindex = 0;
  }
  free(cdata);
}
