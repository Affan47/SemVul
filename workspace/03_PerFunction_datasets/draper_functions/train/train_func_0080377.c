_ungroup (GESContainer * group, gboolean recursive)
{
  GList *children, *tmp, *ret = NULL;

  children = ges_container_get_children (group, FALSE);
  for (tmp = children; tmp; tmp = tmp->next) {
    GESTimelineElement *child = tmp->data;

    gst_object_ref (child);
    ges_container_remove (group, child);
    ret = g_list_append (ret, child);
  }
  g_list_free_full (children, gst_object_unref);


  return ret;
}
