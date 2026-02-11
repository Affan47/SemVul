gtk_plot_canvas_thaw(GtkPlotCanvas *canvas)
{
  if(canvas->freeze_count == 0) return;
  canvas->freeze_count--;
}
