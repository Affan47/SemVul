expPrintifyRealUni(s,numchars)
Tcl_UniChar *s;
int numchars;
{
  static int destlen = 0;
  static char *dest = 0;
  char *d;
  unsigned int need;
  Tcl_UniChar ch;

  if (s == 0) return("<null>");
  if (numchars == 0) return("");


  need = numchars*6 + 1;
  if (need > destlen) {
    if (dest) ckfree(dest);
    dest = ckalloc(need);
    destlen = need;
  }

  for (d = dest;numchars > 0;numchars--) {
    ch = *s; s++;

    if (ch == '\r') {
      strcpy(d,"\\r");		d += 2;
    } else if (ch == '\n') {
      strcpy(d,"\\n");		d += 2;
    } else if (ch == '\t') {
      strcpy(d,"\\t");		d += 2;
    } else if ((ch < 0x80) && isprint(UCHAR(ch))) {
      *d = (char)ch;			d += 1;
    } else {
      sprintf(d,"\\u%04x",ch);	d += 6;
    }
  }
  *d = '\0';
  return(dest);
}
