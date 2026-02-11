glade_gtk_box_verify_size (GObject *object, const GValue *value)
{
  GList *child, *children;
  gint old_size, count = 0;
  gint new_size = g_value_get_int (value);

  children = gtk_container_get_children (GTK_CONTAINER (object));
  old_size = g_list_length (children);

  for (child = g_list_last (children);
       child && old_size > new_size;
       child = g_list_previous (child))
    {
      GtkWidget *widget = child->data;
      if (glade_widget_get_from_gobject (widget) != NULL)
        count++;
      else
        old_size--;
    }

  g_list_free (children);

  return count > new_size ? FALSE : new_size >= 0;
}
