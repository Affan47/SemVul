static_ok (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
GtkWidget *dialog = window->dialog0;
GtkWidget *button;


if (list.indices == NULL)
  {
  gamgi_gtk_dialog_message_create ("Error", "Invalid direction data", window);
  return;
  }


button = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "button_list");
g_signal_handlers_block_by_func (button, gamgi_gtk_direction_list, window);
gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), FALSE);
g_signal_handlers_unblock_by_func (button, gamgi_gtk_direction_list, window);

if (window->dialog1 != NULL)
  gamgi_gtk_dialog_task1_remove (widget, window);

gamgi_gtk_direction_create_uvw (FALSE, window);
}
