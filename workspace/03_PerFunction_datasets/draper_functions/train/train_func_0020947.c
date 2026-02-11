write_ary(char **ary, int sz, int DEST, const char *dest)
{
  FILE *fp;

  if (!DEST) {
     write_ary_to_stream(stdout, ary, sz);
  }
  else if (DEST & OVERWRITE) {
     if ((fp = fopen(dest, "w+")) != NULL) {
       write_ary_to_stream(fp, ary, sz);
     }
     else {
       fprintf(stderr, "Could not write to file: %s\n", dest);
       return 1;
     }
     return fclose(fp);
  }
  else if (DEST & APPEND) {
    if ((fp = fopen(dest, "a+")) != NULL) {
      write_ary_to_stream(fp, ary, sz);
    }
    else {
      fprintf(stderr, "Could not append to file: %s\n", dest);
    }
    return fclose(fp);
   }
  else {
    fprintf(stderr, "Error: For some reason, I don't know where to write to. This cannot be good. See 'write --help'.\n");
    return 1;
  }
  return 0;
}
