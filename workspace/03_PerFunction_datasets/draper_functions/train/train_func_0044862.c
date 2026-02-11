selection_get_line_type(GList *selection,
                                        OBJECT_END *end, OBJECT_TYPE *type,
                                        gint *width, gint *length, gint *space)
{
  GList *iter;
  OBJECT *object;
  gboolean found = FALSE;
  OBJECT_END oend;
  OBJECT_TYPE otype;
  gint owidth, olength, ospace;

  for (iter = selection; iter != NULL; iter = g_list_next(iter)) {
    object = (OBJECT *) iter->data;
    if (! o_get_line_options(object, &oend, &otype,
                             &owidth, &olength, &ospace))
      continue;

    if (found == FALSE) {
      found = TRUE;
      *end = oend;
      *type = otype;
      *width = owidth;
      *length = olength;
      *space = ospace;
    } else {

      if (*end != oend) *end = -2;
      if (*type != otype) *type = -2;
      if (*width != owidth) *width = -2;
      if (*length != olength) *length = -2;
      if (*space != ospace) *space = -2;
    }
  }

  return found;
}
