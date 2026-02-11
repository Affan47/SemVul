CheckFileReadError(FILE * source)
{
  if (ferror(source)) {
    printf("\nError in reading Definitions.txt.\n");
    fclose(source);
    exit(-1);
  }
}
