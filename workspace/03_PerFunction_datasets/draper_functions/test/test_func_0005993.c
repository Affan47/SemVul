indent_surface(const char *s)
{
  const char *p;

  while ((p = strchr(s, '\n')) != NULL) {
    p++;
    printf("  %.*s", (int)(p-s), s);
    s = p;
  }
}
