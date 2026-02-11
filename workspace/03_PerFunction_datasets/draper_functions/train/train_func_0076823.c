se_find_object (se_t *se, se_o_t *parent, const char *name)
{
  GList *objs;
  while (strchr (name, '.'))
  {
    int index = strchr (name, '.') - name;
    foreach_glist (objs, parent ? parent->children : se->g->children)
    {
      se_o_t *o = objs->data;
      if (!strncasecmp (o->id, name, index) && !o->id[index])
      {
	name += index + 1;
	parent = o;
	break;
      }
    }
    if (!objs)
      return NULL;
  }
  foreach_glist (objs, parent ? parent->children : se->g->children)
  {
    se_o_t *o = objs->data;
    if (!strcasecmp (o->id, name))
      return o;
  }
  return NULL;
}
