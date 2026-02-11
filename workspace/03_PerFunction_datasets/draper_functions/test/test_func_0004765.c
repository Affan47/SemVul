gtk_plot_remove_data(GtkPlot *plot, GtkPlotData *dataset)
{
  GList *datasets;
  gpointer data;

  datasets = plot->data_sets;

  while(datasets)
   {
     data = datasets->data;

     if(GTK_PLOT_DATA(data) == dataset){
          gtk_widget_unref(GTK_WIDGET(dataset));
          plot->data_sets = g_list_remove_link(plot->data_sets, datasets);
          g_list_free_1(datasets);
          gtk_signal_emit (GTK_OBJECT(plot), plot_signals[CHANGED]);
	  return TRUE;
     }
     datasets = datasets->next;
   }

  return FALSE;
}
