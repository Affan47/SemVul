grab(FILE *fp, int n, double *list)
{
  char *ptr;
  char line[MAXLINE];

  int i = 0;
  while (i < n) {
    fgets(line,MAXLINE,fp);
    ptr = strtok(line," \t\n\r\f");
    list[i++] = atof(ptr);
    while (ptr = strtok(NULL," \t\n\r\f")) list[i++] = atof(ptr);
  }
}
