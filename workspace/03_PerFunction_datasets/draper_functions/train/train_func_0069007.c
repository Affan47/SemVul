CanReadFile(const char *filename)
{
  FILE *fd = fopen(filename, "rb");
  if (!fd) return 0;

  char line[4] = {};
  const char *result = fgets(line, sizeof(line), fd);
  fclose(fd);
  return (result && strncmp(result, "ply", 3) == 0);
}
