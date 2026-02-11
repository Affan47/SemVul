count_words(const char *line)
{
  int n = strlen(line) + 1;
  char *copy;
  memory->create(copy,n,"atom:copy");
  strcpy(copy,line);

  char *ptr;
  if (ptr = strchr(copy,'#')) *ptr = '\0';

  if (strtok(copy," \t\n\r\f") == NULL) {
    memory->destroy(copy);
    return 0;
  }
  n = 1;
  while (strtok(NULL," \t\n\r\f")) n++;

  memory->destroy(copy);
  return n;
}
