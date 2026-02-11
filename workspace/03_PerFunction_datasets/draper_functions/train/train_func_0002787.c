get_token(int* i, char* s){
  char** pp = NULL, *aux = NULL;
  int c = 0, n;

  if(s != NULL){
    aux = calloc((size_t)strlen(s)+1, sizeof(char));
    strcpy(aux, s);

    if(strtok(aux, " \t") != NULL){
      c++;
      for(; strtok(NULL, " \t") != NULL; )
	c++;

      free(aux);


      pp = calloc((size_t)c+1, sizeof(char*));
      *pp = NULL;
      *(pp+1) = strtok(s, " \t");

      for(n=2; n <= c; n++)
	*(pp+n) = strtok(NULL, " \t");
    }
  }else{
    i = 0;
    return NULL;
  }
  *i = c;
  return pp;
}
