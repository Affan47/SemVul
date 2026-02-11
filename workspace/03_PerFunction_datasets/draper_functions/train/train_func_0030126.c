iobfungetc(int c, IOBFILE *iobf)
{
  if (c == EOF) {
    iobf->ungetc = EOF;
  } else {
    iobf->ungetc = c & 0xff;
    if (iobf->eof == -1){
      iobf->eof = 1;
    }
  }
  return c;
}
