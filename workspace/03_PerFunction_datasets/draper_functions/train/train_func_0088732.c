conditionFalse()
{
  int     level;

  if( line[lexstart] == '<' )
  {

    level = 1;
    while( level > 0 )
    {
      if( isend( line[cc] ) || ( line[cc] == '/' ))
      {
        readLine();
      }
      else
      {
        switch( line[cc] )
        {
        case '>':
          level--;
          cc++;
          break;

        case '<':
          level++;
          cc++;
          break;

        case '$':
          level = 0;
          cc++;
          break;

        default:
          cc++;
          break;
        }
      }
    }
    nextLexeme();
  }
  else
  {
    errorMessage( &lt_expected, lexstart );
  }
}
