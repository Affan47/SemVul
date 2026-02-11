gtk_plot_set_break         	(GtkPlot *plot,
                                                 GtkPlotOrientation orient,
                                                 gdouble min, gdouble max,
                                                 gdouble step_after,
                                                 gint nminor_after,
                                                 GtkPlotScale scale_after,
                                                 gdouble pos)
{
  if(orient == GTK_PLOT_AXIS_X){
    gtk_plot_axis_set_break(plot->top, min, max, step_after, nminor_after, scale_after, pos);
    gtk_plot_axis_set_break(plot->bottom, min, max, step_after, nminor_after, scale_after, pos);
  } else {
    gtk_plot_axis_set_break(plot->left, min, max, step_after, nminor_after, scale_after, pos);
    gtk_plot_axis_set_break(plot->right, min, max, step_after, nminor_after, scale_after, pos);
  }
}
