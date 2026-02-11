photos_dlna_renderers_separator_cb (GtkListBoxRow *row,
                                    GtkListBoxRow *before,
                                    gpointer user_data)
{
  GtkWidget *separator;

  separator = gtk_list_box_row_get_header (row);
  if (separator == NULL && before != NULL)
    {
      separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
      gtk_list_box_row_set_header (row, separator);
      gtk_widget_show (separator);
    }
}
