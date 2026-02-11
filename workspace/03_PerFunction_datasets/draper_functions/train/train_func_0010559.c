gtk_plot_surface_get_legend_size(GtkPlotData *data, gint *width, gint *height)
{
  GtkPlotSurface *surface;
  GtkPlot *plot = NULL;
  GtkPlotText legend;
  gint lascent = 0, ldescent = 0, lheight = 0, lwidth = 0;
  gdouble m;

  surface = GTK_PLOT_SURFACE(data);

  g_return_if_fail(data->plot != NULL);
  g_return_if_fail(GTK_IS_PLOT(data->plot));

  plot = data->plot;

  m = plot->magnification;
  legend = plot->legends_attr;

  if(data->legend && strlen(data->legend) > 0)
    legend.text = data->legend;
  else
    legend.text = "X";

  *height = 0;
  *width = roundint(16*m);

  if(data->show_legend){
    int lstep = roundint(plot->legends_line_width * m / 10.);
    double step = (data->gradient->ticks.max - data->gradient->ticks.min) / 10;
    double level;
    for(level = data->gradient->ticks.min; level < data->gradient->ticks.max; level += step) *width += lstep;

    gtk_plot_text_get_size(legend.text, legend.angle, legend.font,
                           roundint(legend.height * m),
                           &lwidth, &lheight,
                           &lascent, &ldescent);
    *height = *height + lascent + ldescent;
    *width = *width + lwidth;
  }
}
