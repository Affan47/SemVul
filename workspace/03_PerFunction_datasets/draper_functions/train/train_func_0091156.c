gtk_plot_canvas_get_property (GObject      *object,
                              guint            prop_id,
                              GValue          *value,
                              GParamSpec      *pspec)
{
  GtkPlotCanvas *canvas = GTK_PLOT_CANVAS(object);

  switch(prop_id){
    case ARG_CANVAS_FLAGS:
      g_value_set_int(value, canvas->flags);
      break;
    case ARG_CANVAS_WIDTH:
      g_value_set_int(value, canvas->width);
      break;
    case ARG_CANVAS_HEIGHT:
      g_value_set_int(value, canvas->height);
      break;
    case ARG_CANVAS_MAGNIFICATION:
      g_value_set_double(value, canvas->magnification);
      break;
    case ARG_CANVAS_SHOW_GRID:
      g_value_set_boolean(value, canvas->show_grid);
      break;
    case ARG_CANVAS_GRID_STEP:
      g_value_set_double(value, canvas->grid_step);
      break;
    case ARG_CANVAS_LINE_GRID:
      g_value_set_pointer(value, &canvas->grid);
      break;
    case ARG_CANVAS_COLOR_BG:
      g_value_set_pointer(value, &canvas->background);
      break;
    case ARG_CANVAS_TRANSPARENT:
      g_value_set_boolean(value, canvas->transparent);
      break;
  }
}
