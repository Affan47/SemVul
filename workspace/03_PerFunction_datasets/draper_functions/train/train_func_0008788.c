read_string(char *inbuf)
{
  char *ptr;
  char *boundary;
  int c;
  int cnt;

  boundary = inbuf + BUF_SIZE - 1;
  ptr = inbuf;
  *ptr = '\0';
  while ((c = getchar()) != EOF && c != '\0')
    {
      if (ptr < boundary)
        *ptr++ = c;
      else
        break;
    }

  if (c == EOF)
    {
      if (ferror(stdin))
        {
          perror("read_string");
          return(-1);
        }
      else if (feof(stdin))
        return(-1);
    }
  *ptr = '\0';
  return(strlen(inbuf));
}
