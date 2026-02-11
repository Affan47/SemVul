replace_widget(GtkWidget *old, GtkWidget *new)
{
  GtkWidget *parent;

  parent = gtk_widget_get_parent(old);
  if (!parent) {
    return;
  }

  gtk_container_remove(GTK_CONTAINER(parent), old);
  gtk_box_pack_start(GTK_BOX(parent), new, FALSE, FALSE, 0);
}
