gtk_plot_data_required_dimensions(GtkPlotData *data)
{
  guint n = 0;
  GtkPlotArrayList *dims = data->data;
  GList *list = dims->arrays;
  while(list){
    GtkPlotArray *dim = GTK_PLOT_ARRAY(list->data);
    if(dim->required) n++;
    list = list->next;
  }
  return n;
}
