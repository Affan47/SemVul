gtk_plot_data_point_clipped(GtkPlotData *data, gdouble x, gdouble y, gdouble z, gdouble a, gboolean connector)
{
  GtkPlot *plot;

  plot = data->plot;

  if(GTK_IS_PLOT_POLAR(plot)){
    GtkPlotPolar *polar = GTK_PLOT_POLAR(plot);
    if(plot->clip_data &&
       (x < polar->r->ticks.min || x > polar->r->ticks.max || y < polar->angle->ticks.min || y > polar->angle->ticks.max))
             return TRUE;
  } else if(GTK_IS_PLOT3D(plot)){
    if(plot->clip_data && (x < plot->xmin || x > plot->xmax)) return TRUE;
    if(plot->clip_data && data->symbol.symbol_type != GTK_PLOT_SYMBOL_IMPULSE &&
       (y < plot->ymin || y > plot->ymax)) return TRUE;
  } else {
    if(plot->clip_data && !connector &&
       (x < plot->xmin || x > plot->xmax || y < plot->ymin || y > plot->ymax))
             return TRUE;
  }

  return FALSE;
}
