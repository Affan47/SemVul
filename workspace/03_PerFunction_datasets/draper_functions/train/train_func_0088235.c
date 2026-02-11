se_get_object (se_t *se, se_o_t *parent, const char *name)
{
  se_o_t *o = se_find_object (se, parent, name);
  if (o)
    return o;
  free (dflt.id);
  dflt.id = strdup (name);
  return &dflt;
}
