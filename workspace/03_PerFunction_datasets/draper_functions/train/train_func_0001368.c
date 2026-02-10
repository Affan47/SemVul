glade_gtk_assistant_get_children (GladeWidgetAdaptor *adaptor,
                                  GObject *container)
{
  GtkAssistant *assist = GTK_ASSISTANT (container);
  gint i, n_pages = gtk_assistant_get_n_pages (assist);
  GList *children = NULL, *parent_children;


  if (GWA_GET_CLASS (GTK_TYPE_WINDOW)->get_children)
    parent_children = GWA_GET_CLASS (GTK_TYPE_WINDOW)->get_children (adaptor, container);
  else
    parent_children = NULL;

  for (i = 0; i < n_pages; i++)
    children = g_list_prepend (children, gtk_assistant_get_nth_page (assist, i));

  children = g_list_reverse (children);

  return glade_util_purify_list (g_list_concat (children, parent_children));
}
