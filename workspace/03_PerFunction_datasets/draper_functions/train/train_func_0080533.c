recent_menu_setup_callbacks (GtkWidget *menu, GladeWindow *window)
{
  GList *l, *list = gtk_container_get_children (GTK_CONTAINER (menu));

  for (l = list; l; l = g_list_next (l))
    menu_item_connect (l->data, NULL, window);

  g_list_free (list);
}
