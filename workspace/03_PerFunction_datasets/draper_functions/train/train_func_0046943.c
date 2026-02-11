isNumber(const char* str)
{
  if ( str == NULL || str[0] == '\0' )
    return false;

  int len = strlen(str);
  int index = 0;

  char* tmp = (char*)str;


  if (tmp[0] == '-' || tmp[0] == '+' ) {
    tmp++;
    index++;
  }


  if ( index == len || !isdigit(tmp[0]) )
    return false;


  while ( index < len && isdigit(tmp[0]) ) {
    tmp++;
    index++;
  }


  if ( index == len )
    return true;


  if ( tmp[0] == '.' ) {
    tmp++;
    index++;
  }


  while ( index < len && isdigit(tmp[0]) ) {
    tmp++;
    index++;
  }


  if ( index == len )
    return true;


  if ( tmp[0] == 'E' ||
       tmp[0] == 'e' ||
       tmp[0] == 'D' ||
       tmp[0] == 'd'
     ) {
    tmp++;
    index++;


  } else {
    return false;
  }


  if ( index == len )
    return false;


  if (tmp[0] == '-' || tmp[0] == '+' ) {
    tmp++;
    index++;
  }


  if ( index == len || !isdigit(tmp[0]) )
    return false;


  while ( index < len && isdigit(tmp[0]) ) {
    tmp++;
    index++;
  }


  if ( index < len )
    return false;

  else
    return true;
}
