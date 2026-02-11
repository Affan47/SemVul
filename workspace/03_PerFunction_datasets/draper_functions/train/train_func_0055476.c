gtk_plot_surface_add_to_plot (GtkPlotData *data, GtkPlot *plot)
{
  if(!data->is_function && data->num_points > 0){
    gtk_plot_surface_build_mesh(GTK_PLOT_SURFACE(data));
  }

  data->redraw_pending = TRUE;

  return TRUE;
}
