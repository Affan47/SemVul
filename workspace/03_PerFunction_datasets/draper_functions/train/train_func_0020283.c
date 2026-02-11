_http_trim( char *string, const int max_len )
{
  int i, j;


  for( i=0; i<max_len && string[i]!='\0'; ++i )
  {
    if( string[i] == '\t' )
    {
      string[i] = ' ';
    }

    if( string[i] == '\r'  || string[i] == '\n' )
    {
      string[i] = '\0';
    }
  }


  for( i=0; i<max_len && string[i]!='\0'; ++i )
  {
    if( ! ( string[i] == ' ' ) )
      break;
  }


  for( j=0; i<max_len && string[i]!='\0'; ++i, j++ )
  {
    string[j] = string[i];
  }
  string[j] = '\0';


  for( --i; i > 0 ; --i )
  {
    if( ! ( string[i] == ' ' ) )
      break;
  }


  string[++i] = '\0';
}
