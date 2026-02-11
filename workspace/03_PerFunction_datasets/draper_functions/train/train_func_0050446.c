fixAddition( char *url, char *addition )
{
  if ( addition ) {
    char	*result = (char *)MALLOC( strlen( url ) + strlen( addition ) + 1 );
    int		i;

    for ( i = 0 ; url[i] && url[i] != '?' ; ++i ) {
      result[i] = url[i];
    }
    result[i] = '?';
    result[i+1] = '\0';
    strcat( result, addition );

    return result;
  } else {
    return STRDUP( url );
  }
}
