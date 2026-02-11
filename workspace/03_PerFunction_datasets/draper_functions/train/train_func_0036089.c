egetc() {

  int c = (*Mf_getc)();

  if ( c == EOF )
    mferror("premature EOF");
  Mf_toberead--;
  return(c);
}
