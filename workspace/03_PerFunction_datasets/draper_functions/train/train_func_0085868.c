skipwhitechars(FILE*f)
{
  int c;
  while (1)
    {
      c=getc(f);

      switch(c){
      case ' ': case '\t': case '\r': case '\n':
	break;
      case EOF:
	return 1;
      default:
	ungetc(c, f);
	return 0;
      }
    }
}
