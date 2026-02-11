gtk_plot_canvas_line_new (GtkPlotLineStyle style,
                          gfloat width,
                          const GdkColor *color,
                          GtkPlotCanvasArrow arrow_mask)
{
  GtkPlotCanvasLine *line;

  line = gtk_type_new (gtk_plot_canvas_line_get_type ());

  line->line.line_width = width;
  if(color) line->line.color = *color;
  line->arrow_mask = arrow_mask;

  return GTK_PLOT_CANVAS_CHILD (line);
}
