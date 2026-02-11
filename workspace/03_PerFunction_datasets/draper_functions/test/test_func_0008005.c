builtin_ask(MYSQL *mysql __attribute__((unused)),
                         int type __attribute__((unused)),
                         const char *prompt,
                         char *buf, int buf_len)
{
  char *ptr;
  fputs(prompt, stdout);
  fputc(' ', stdout);
  if (fgets(buf, buf_len, stdin) == NULL)
    return NULL;
  if ((ptr= strchr(buf, '\n')))
    *ptr= 0;

  return buf;
}
