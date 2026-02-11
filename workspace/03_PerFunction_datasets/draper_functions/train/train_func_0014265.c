trimWhiteSpace(char *pChar){

  int i;

  if (!pChar) return NULL;


  i = strlen(pChar)-1;
  while( (i > -1) && (pChar[i] == ' ') ){
    pChar[i--] = '\0';
  }

  return pChar;
}
