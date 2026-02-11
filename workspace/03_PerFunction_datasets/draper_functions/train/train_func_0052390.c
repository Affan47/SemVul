gtk_plot_csurface_init (GtkPlotCSurface *dataset)
{
  GtkWidget *widget;
  GdkColormap *colormap;
  GtkPlotArray *dim;

  GTK_WIDGET_SET_FLAGS(dataset, GTK_NO_WINDOW);

  widget = GTK_WIDGET(dataset);
  colormap = gtk_widget_get_colormap(widget);

  GTK_PLOT_DATA(dataset)->show_gradient = TRUE;
  GTK_PLOT_DATA(dataset)->show_labels = TRUE;
  GTK_PLOT_DATA(dataset)->gradient_custom = TRUE;

  GTK_PLOT_SURFACE(dataset)->show_mesh = TRUE;

  dataset->lines_visible = TRUE;
  dataset->projection = GTK_PLOT_PROJECT_EMPTY;
  dataset->levels = NULL;
  dataset->bg_triangles = NULL;

  GTK_PLOT_DATA(dataset)->labels_attr.height = 10;

  dataset->levels_line = GTK_PLOT_SURFACE(dataset)->mesh_line;
  dataset->sublevels_line = GTK_PLOT_SURFACE(dataset)->mesh_line;
  dataset->sublevels_line.line_style = GTK_PLOT_LINE_DASHED;

  dim = gtk_plot_data_find_dimension(GTK_PLOT_DATA(dataset), "y");
  gtk_plot_array_set_independent(dim, TRUE);
  dim = gtk_plot_data_find_dimension(GTK_PLOT_DATA(dataset), "z");
  gtk_plot_array_set_required(dim, TRUE);
}
