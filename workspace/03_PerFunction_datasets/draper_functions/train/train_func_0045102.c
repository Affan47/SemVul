gtk_plot_csurface_draw_legend(GtkPlotData *data, gint x, gint y)
{
  GtkPlotSurface *surface;
  GtkPlotCSurface *csurface;
  GtkPlot *plot = NULL;
  GtkPlotText legend;
  GdkRectangle area;
  gint lascent = 0, ldescent = 0, lheight = 0, lwidth = 0;
  gdouble m;

  surface = GTK_PLOT_SURFACE(data);
  csurface = GTK_PLOT_CSURFACE(data);

  g_return_if_fail(data->plot != NULL);
  g_return_if_fail(GTK_IS_PLOT(data->plot));

  plot = data->plot;
  area.x = GTK_WIDGET(plot)->allocation.x;
  area.y = GTK_WIDGET(plot)->allocation.y;
  area.width = GTK_WIDGET(plot)->allocation.width;
  area.height = GTK_WIDGET(plot)->allocation.height;

  m = plot->magnification;
  legend = plot->legends_attr;

  if(data->legend)
    legend.text = data->legend;
  else
    legend.text = "X";

  gtk_plot_text_get_size(legend.text, legend.angle, legend.font,
                         roundint(legend.height * m),
                         &lwidth, &lheight,
                         &lascent, &ldescent);

  if(GTK_PLOT_DATA(data)->show_legend && data->legend && strlen(data->legend) > 0){
    legend.x = (gdouble)(area.x + x + roundint(4 * m))
               / (gdouble)area.width;
    legend.y = (gdouble)(area.y + y + lascent) / (gdouble)area.height;

    gtk_plot_draw_text(plot, legend);
    y += 2 * lheight;
  } else
    y += lheight;

  GTK_PLOT_DATA(data)->gradient_custom = TRUE;
}
