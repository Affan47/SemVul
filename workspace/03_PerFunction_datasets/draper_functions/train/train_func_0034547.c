s_stretch_add (GList *list, OBJECT *object, int whichone)
{
  GList *s_iter;
  STRETCH *s_new;


  for (s_iter = list; s_iter != NULL; s_iter = g_list_next (s_iter)) {
    STRETCH *s_current = s_iter->data;
    if (s_current->object->sid == object->sid) {
      return list;
    }
  }

  s_new = g_malloc (sizeof (STRETCH));
  s_new->object = object;
  s_new->whichone = whichone;

  return g_list_append (list, s_new);
}
