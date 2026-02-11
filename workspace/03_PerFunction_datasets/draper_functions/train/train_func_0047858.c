skip_list (FILE *fp, char *filename, char *subsetname) {
  char Buffer[BUFSIZE];

  if (fgets(Buffer,BUFSIZE,fp) == NULL) {
    fprintf(stderr,"In %s, expected a line after >%s\n",filename,subsetname);
    exit(9);
  }
  return;
}
