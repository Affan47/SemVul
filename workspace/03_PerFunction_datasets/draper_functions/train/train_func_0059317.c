gtk_plot_canvas_plot_move		(GtkPlotCanvas *canvas,
					 GtkPlotCanvasChild *child,
					 gdouble x, gdouble y)
{
  GtkPlotCanvasPlot *cplot = GTK_PLOT_CANVAS_PLOT(child);
  GtkPlot *plot = cplot->plot;
  if(!plot) return;
}
