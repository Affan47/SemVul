gamgi_gtk_gamgi_exit_ok (GtkWidget *widget, void *data)
{
gamgi_window *window;


gamgi_mesa_lists_remove ();
g_source_remove (gamgi->timer_time);


gamgi_gtk_dialog_global_remove ();


gamgi_global_selection_remove_all ();


for (window = gamgi->window_start; window != NULL; window = window->next)
  gamgi_gtk_window_remove_dialogs (window);

for (window = gamgi->window_start; window != NULL; window = window->next)
  {
  gamgi_gtk_window_remove_timers (window);
  gamgi_gtk_window_remove_window (window);
  }


gtk_main_quit ();
}
