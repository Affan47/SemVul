gtk_plot3d_minor_zgrid_set_attributes    (GtkPlot3D *plot,
                                         GtkPlotLineStyle style,
                                         gfloat width,
                                         const GdkColor *color)
{
  plot->az->minor_grid.line_style = style;
  plot->az->minor_grid.line_width = width;
  if(color) plot->az->minor_grid.color = *color;
}
