update_datasets(GtkPlot *plot, gboolean new_range)
{
  GList *list = NULL;

  list = plot->data_sets;
  while(list) {
    gtk_signal_emit_by_name(GTK_OBJECT(list->data), "update", new_range);

    list = list->next;
  }
}
