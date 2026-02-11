gtk_plot_canvas_set_property (GObject      *object,
                              guint            prop_id,
                              const GValue          *value,
                              GParamSpec      *pspec)
{
  GtkPlotCanvas *canvas;

  canvas = GTK_PLOT_CANVAS (object);

  switch(prop_id){
    case ARG_CANVAS_FLAGS:
      canvas->flags = g_value_get_int(value);
      break;
    case ARG_CANVAS_WIDTH:
      canvas->width = g_value_get_int(value);
      break;
    case ARG_CANVAS_HEIGHT:
      canvas->height = g_value_get_int(value);
      break;
    case ARG_CANVAS_MAGNIFICATION:
      canvas->magnification = g_value_get_double(value);
      break;
    case ARG_CANVAS_SHOW_GRID:
      canvas->show_grid = g_value_get_boolean(value);
      break;
    case ARG_CANVAS_GRID_STEP:
       canvas->grid_step = g_value_get_double(value);
      break;
    case ARG_CANVAS_LINE_GRID:
      canvas->grid = *((GtkPlotLine *)g_value_get_pointer(value));
      break;
    case ARG_CANVAS_COLOR_BG:
      canvas->background = *((GdkColor *)g_value_get_pointer(value));
      break;
    case ARG_CANVAS_TRANSPARENT:
      canvas->transparent = g_value_get_boolean(value);
      break;
  }
}
