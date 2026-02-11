escapeString( char* string ) {
  int i, length;
  char* result;
  char* resultP;
  int charsToEscape = 0;


  i = 0;
  while (string[i] != '\0') {
    if( string[i] == '/' ) {
      ++charsToEscape;
    }

    ++i;
  }


  length = i;


  if(! (result = (char *)malloc( length + charsToEscape + 1 )) ) {
    print_error("Malloc failed - out of memory");
    exit(1);
  }
  resultP = result;

  i = 0;
  while (string[i] != '\0') {
    if( string[i] == '/' ) {
      resultP[0] = '\\';
      resultP++;
    }
    resultP[0] = string[i];
    resultP++;

    ++i;
  }
  resultP[0] = '\0';
  return result;
}
