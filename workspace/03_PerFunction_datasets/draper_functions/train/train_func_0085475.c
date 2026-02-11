my_strcasecmp ( char *str1, char *str2 )
{
  char *ptr1, *ptr2, *ptr;
  int ret;

  ptr1 = strdup ( str1 );
  ptr2 = strdup ( str2 );

  for ( ptr = ptr1; *ptr != '\0'; ptr++ ) {
    *ptr = toupper ( *ptr );
  }
  for ( ptr = ptr2; *ptr != '\0'; ptr++ ) {
    *ptr = toupper ( *ptr );
  }

  ret = strcmp ( ptr1, ptr2 );
  free ( ptr1 );
  free ( ptr2 );
  return ( ret );
}
