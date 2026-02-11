_auth_lb_create (struct _line_buffer **s)
{
  *s = malloc (sizeof (**s));
  if (!*s)
    return ENOMEM;
  (*s)->buffer = NULL;
  (*s)->size = 0;
  (*s)->level = 0;
  return 0;
}
