gtk_plot_data_set_legend(GtkPlotData *dataset,
                            const gchar *legend)
{
  if(legend){
     g_free(dataset->legend);
     dataset->legend = g_strdup(legend);
  }
}
