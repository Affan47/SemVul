get_num(FILE * f)
{
  unsigned int num;
  int c;

  while(isspace(c=getc(f)));
  if(!isdigit(c)) error("corrupted PGM file.");
  num = (unsigned int) (c - '0');
  while( isdigit(c=getc(f)) ) num = 10 * num + c - '0';
  if( c != EOF && ungetc(c,f) == EOF )
    error("unable to 'ungetc' while reading PGM file.");

  return num;
}
