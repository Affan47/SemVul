tg_tag (void *p ATTRIBUTE_UNUSED, const char *name ATTRIBUTE_UNUSED)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *t;

  t = pop_type (info);
  if (t == NULL)
    return FALSE;
  free (t);

  return TRUE;
}
