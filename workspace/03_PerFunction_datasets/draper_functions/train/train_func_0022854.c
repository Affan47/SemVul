escapedStringToWString(char* s) {
  int         len = strlen(s);
  IDL_UShort* ret = new IDL_UShort[len+1];
  char        tmp[8];

  int from, to, i;

  for (from=0, to=0; from < len; from++, to++) {

    if (s[from] == '\\') {
      tmp[0] = s[from++];

      if ('0' <= s[from] && s[from] <= '7') {

	for (i=1;
	     i < 4 && from < len && '0' <= s[from] && s[from] <= '7';
	     from++, i++) tmp[i] = s[from];

	tmp[i]  = '\0';
	ret[to] = octalToWChar(tmp);
	from--;
      }
      else if (s[from] == 'x') {

	tmp[1] = s[from++];
	for (i=2; i < 4 && from < len && isxdigit(s[from]); from++, i++)
	  tmp[i] = s[from];

	tmp[i]  = '\0';
	ret[to] = hexToWChar(tmp);
	from--;
      }
      else if (s[from] == 'u') {

	tmp[1] = s[from++];
	for (i=2; i < 6 && from < len && isxdigit(s[from]); from++, i++)
	  tmp[i] = s[from];

	tmp[i]  = '\0';
	ret[to] = hexToWChar(tmp);
	from--;
      }
      else {
	tmp[1]  = s[from];
	tmp[2]  = '\0';
	ret[to] = escapeToWChar(tmp);
      }
      if (ret[to] == 0) {
	IdlError(currentFile, yylineno,
		 "Wide string cannot contain wide character zero");
	ret[to] = '!';
      }
    }
    else
      ret[to] = s[from];
  }
  ret[to] = 0;
  return ret;
}
