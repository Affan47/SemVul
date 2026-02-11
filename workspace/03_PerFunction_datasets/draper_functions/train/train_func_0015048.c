getline(char *s, size_t n, FILE *fd)
{ int c;
  char *t = s;
  if (n)
    n--;
  for (;;)
  { c = fgetc(fd);
    if (c == '\r')
      continue;
    if (c == '\\')
    { c = fgetc(fd);
      if (c == '\r')
        c = fgetc(fd);
      if (c < ' ')
        continue;
      if (n)
      { *t++ = '\\';
        n--;
      }
    }
    if (c == '\n' || c == EOF)
      break;
    if (n)
    { *t++ = c;
      n--;
    }
  }
  *t++ = '\0';
  if (!*s && c == EOF)
    return NULL;
  return s;
}
