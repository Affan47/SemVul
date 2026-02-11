stop_drag_check (GtkWidget *widget)
{
  EggTreeMultiDndData *priv_data;
  GSList *l;

  priv_data = g_object_get_data (G_OBJECT (widget), EGG_TREE_MULTI_DND_STRING);

  for (l = priv_data->event_list; l != NULL; l = l->next)
    gdk_event_free (l->data);

  g_slist_free (priv_data->event_list);
  priv_data->event_list = NULL;
}
