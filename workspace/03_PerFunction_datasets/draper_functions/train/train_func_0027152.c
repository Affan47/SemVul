vary_append(struct vary *v, char *arg)
{
  struct vary *result, **nextp;

  if (v) {
    result = v;
    while (v->next)
      v = v->next;
    nextp = &v->next;
  } else
    nextp = &result;

  if ((*nextp = (struct vary *)malloc(sizeof(struct vary))) == NULL)
    exifdie((const char *)strerror(errno));
  (*nextp)->arg = arg;
  (*nextp)->next = NULL;
  return result;
}
