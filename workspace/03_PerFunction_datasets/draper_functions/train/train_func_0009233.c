static_cell (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
gamgi_cell *cell;
GtkWidget *dialog = window->dialog0;
GtkWidget *vbox_scope, *vbox_projection;

vbox_scope = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "vbox_scope");
vbox_projection = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "vbox_projection");

cell = GAMGI_CAST_CELL gamgi_gtk_object_name_number (dialog,
"entry_cell", GAMGI_ENGINE_CELL, window);
if (cell != NULL && cell->model == GAMGI_PHYS_PROJECTION)
  {
  gtk_widget_hide (vbox_scope);
  gtk_widget_show (vbox_projection);
  static_start_projection (window);
  }
else
  {
  gtk_widget_hide (vbox_projection);
  gtk_widget_show (vbox_scope);
  static_start_scope (window);
  static_nodes (cell, window);
  }

}
