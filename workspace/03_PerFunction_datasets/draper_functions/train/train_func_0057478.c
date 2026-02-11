file_open(lemp,suffix,mode)
struct lemon *lemp;
char *suffix;
char *mode;
{
  FILE *fp;

  if( lemp->outname ) free(lemp->outname);
  lemp->outname = file_makename(lemp, suffix);
  fp = fopen(lemp->outname,mode);
  if( fp==0 && *mode=='w' ){
    fprintf(stderr,"Can't open file \"%s\".\n",lemp->outname);
    lemp->errorcnt++;
    return 0;
  }
  return fp;
}
