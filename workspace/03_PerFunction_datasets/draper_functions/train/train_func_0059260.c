safe_gets(const char *prompt,
          char       *s,
          int        size)
{
  printf("%s ", prompt);

  if (fgets(s, size, stdin) == NULL)
    return (NULL);

  if (s[0])
    s[strlen(s) - 1] = '\0';

  return (s);
}
