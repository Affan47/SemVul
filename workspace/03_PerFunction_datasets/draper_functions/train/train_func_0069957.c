gtk_plot_array_set_label(GtkPlotArray *array, const gchar *label)
{
  if(array->label) g_free(array->label);
  array->label = NULL;
  if(label) array->label = g_strdup(label);
}
