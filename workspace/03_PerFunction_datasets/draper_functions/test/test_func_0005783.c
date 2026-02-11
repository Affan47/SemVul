gui_grid_find(GtkWidget *w, gpointer dialog)
{
GtkEntry *entry;
struct grid_data_pak *grid_data;


if (!grid_task_start())
  return;

entry = dialog_child_get(dialog, "application");

grid_data = grid_data_new();
grid_data->application = g_strdup(gtk_entry_get_text(entry));


task_new("Discovery", grid_find_start, grid_data, grid_find_stop, grid_data, NULL);
}
