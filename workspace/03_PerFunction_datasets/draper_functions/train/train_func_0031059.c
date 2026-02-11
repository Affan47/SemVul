find_array(GtkPlotArrayList *array_list, const gchar *name)
{
  GList *list;

  if(!array_list->arrays) return NULL;

  list = array_list->arrays;
  while(list){
    if(list->data && GTK_IS_PLOT_ARRAY(list->data))
      if(GTK_PLOT_ARRAY(list->data)->name && strcmp(GTK_PLOT_ARRAY(list->data)->name, name) == 0) return list;
    list = list->next;
  }
  return NULL;
}
