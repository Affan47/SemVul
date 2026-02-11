file_makename(lemp,suffix)
struct lemon *lemp;
char *suffix;
{
  char *name;
  char *cp;

  name = malloc( strlen(lemp->filename) + strlen(suffix) + 5 );
  if( name==0 ){
    fprintf(stderr,"Can't allocate space for a filename.\n");
    exit(1);
  }

	if (NULL == (cp = strrchr(lemp->filename, '/'))) {
		cp = lemp->filename;
	} else {
		cp++;
	}
  strcpy(name,cp);
  cp = strrchr(name,'.');
  if( cp ) *cp = 0;
  strcat(name,suffix);
  return name;
}
