property_page_add_extviewer(struct property_page *pp,
                                        struct extviewer *ev)
{
  GtkWidget *w;

  if (!pp || !ev) {
    return;
  }

  w = extviewer_get_view_widget(ev);
  if (!w) {
    return;
  }
  gtk_notebook_append_page(GTK_NOTEBOOK(pp->extviewer_notebook), w, NULL);
}
