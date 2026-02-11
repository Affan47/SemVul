ckey(filename, file)
  char *filename;
  FILE *file;
{
  int ch;

  do {
    ch=fgetc(file);
    ++(freq+1)[ch];
  } while(EOF!=ch);

  if(ferror(file)) {
    perror("error: read");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
