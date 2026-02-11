gtk_plot_data_draw_symbol_private (GtkPlotData *data,
                                   gdouble x, gdouble y,
                                   GtkPlotSymbol symbol)
{
  GtkWidget *widget;
  GtkPlot *plot;
  gdouble x0, y0;
  gdouble px0, py0;
  GdkRectangle clip_area;
  gboolean filled;
  gint size;
  gdouble m;

  if(symbol.symbol_type == GTK_PLOT_SYMBOL_NONE) return;

  plot = data->plot;
  widget = GTK_WIDGET(plot);

  m = plot->magnification;

  clip_area.x = plot->internal_allocation.x;
  clip_area.y = plot->internal_allocation.y;
  clip_area.width = plot->internal_allocation.width;
  clip_area.height = plot->internal_allocation.height;


  gtk_plot_pc_set_color(plot->pc, &symbol.color);
  gtk_plot_pc_set_lineattr (plot->pc, symbol.border.line_width, 0, 0, 0);
  gtk_plot_pc_set_dash (plot->pc, 0, 0, 0);

  filled = (symbol.symbol_style == GTK_PLOT_SYMBOL_FILLED) ? TRUE : FALSE;
  size = symbol.size;

  switch(symbol.symbol_type) {
     case GTK_PLOT_SYMBOL_NONE:
            break;
     case GTK_PLOT_SYMBOL_DOT:
            gtk_plot_pc_draw_point(plot->pc, x, y);
            break;
     case GTK_PLOT_SYMBOL_SQUARE:
            gtk_plot_pc_draw_rectangle (plot->pc,
                                        filled,
                                        x-m*size/2.0, y-m*size/2.0,
                                        m*size, m*size);
            break;
     case GTK_PLOT_SYMBOL_CIRCLE:
            gtk_plot_pc_draw_circle (plot->pc, filled, x, y, m*size);
            break;
     case GTK_PLOT_SYMBOL_UP_TRIANGLE:
            gtk_plot_data_draw_up_triangle (data, x, y, size, filled);
            break;
     case GTK_PLOT_SYMBOL_DOWN_TRIANGLE:
            gtk_plot_data_draw_down_triangle (data, x, y, size, filled);
            break;
     case GTK_PLOT_SYMBOL_RIGHT_TRIANGLE:
            gtk_plot_data_draw_right_triangle (data, x, y, size, filled);
            break;
     case GTK_PLOT_SYMBOL_LEFT_TRIANGLE:
            gtk_plot_data_draw_left_triangle (data, x, y, size, filled);
            break;
     case GTK_PLOT_SYMBOL_DIAMOND:
            gtk_plot_data_draw_diamond (data, x, y, size, filled);
            break;
     case GTK_PLOT_SYMBOL_PLUS:
            gtk_plot_data_draw_plus (data, x, y, size);
            break;
     case GTK_PLOT_SYMBOL_CROSS:
            gtk_plot_data_draw_cross (data, x, y, size);
            break;
     case GTK_PLOT_SYMBOL_STAR:
            gtk_plot_data_draw_star (data, x, y, size);
            break;
     case GTK_PLOT_SYMBOL_IMPULSE:
            x0 = x;
            y0 = 0.;
            gtk_plot_get_pixel(plot, x0, y0, &px0, &py0);
            gtk_plot_pc_draw_line(plot->pc,
                          x, MIN(py0,y),
                          x,
                          MAX(py0,y));
            break;
  }


}
