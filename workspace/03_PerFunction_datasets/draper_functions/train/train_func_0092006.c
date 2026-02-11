file_makename(struct lemon *lemp, const char *suffix)
{
  char *name;
  char *cp;

  name = (char*)malloc( lemonStrlen(lemp->filename) + lemonStrlen(suffix) + 5 );
  if( name==0 ){
    fprintf(stderr,"Can't allocate space for a filename.\n");
    exit(1);
  }
  lemon_strcpy(name,lemp->filename);
  cp = strrchr(name,'.');
  if( cp ) *cp = 0;
  lemon_strcat(name,suffix);
  return name;
}
