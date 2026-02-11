cro_includefile(FILE *outf, Outchoices *od, char *name, char type) {
  FILE *inf;
  char buffer[BLOCKSIZE];
  size_t n;

  if ((inf = my_fopen(name, (type == 'h')?"header file":"footer file")) !=
      NULL) {
    while ((n = fread(buffer, 1, BLOCKSIZE, inf)))
      fwrite((void *)buffer, 1, n, outf);
    (void)my_fclose(inf, name, (type == 'h')?"header file":"footer file");
  }
}
