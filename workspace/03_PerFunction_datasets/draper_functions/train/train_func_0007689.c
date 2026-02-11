handle_D_option(char *z){
  char **paz;
  nDefine++;
  azDefine = realloc(azDefine, sizeof(azDefine[0])*nDefine);
  if( azDefine==0 ){
    fprintf(stderr,"out of memory\n");
    exit(1);
  }
  paz = &azDefine[nDefine-1];
  *paz = malloc( lemonStrlen(z)+1 );
  if( *paz==0 ){
    fprintf(stderr,"out of memory\n");
    exit(1);
  }
  strcpy(*paz, z);
  for(z=*paz; *z && *z!='='; z++){}
  *z = 0;
}
