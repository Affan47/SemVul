pwd(){
  char * pwd;
  if((pwd = getcwd(NULL,0)) == NULL){return 1;}
  else {
    printf("%s\n",pwd);
  }
  free(pwd);
  return 0;
}
