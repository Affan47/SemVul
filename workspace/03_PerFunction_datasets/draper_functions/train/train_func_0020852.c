skip_whites_and_comments(FILE * f)
{
  int c;
  do
    {
      while(isspace(c=getc(f)));
      if(c=='#')
        while( c!='\n' && c!='\r' && c!=EOF )
          c=getc(f);
    }
  while( c == '#' || isspace(c) );
  if( c != EOF && ungetc(c,f) == EOF )
    error("unable to 'ungetc' while reading PGM file.");
}
