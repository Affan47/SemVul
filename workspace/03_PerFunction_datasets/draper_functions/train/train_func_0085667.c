static_ok (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
GtkWidget *dialog = window->dialog0;
gamgi_window_class *window_class, *window_class_old;
GtkWidget *entry;
const char *name;

window_class = gamgi_global_copy_window (gamgi->window);


entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_rotate_max");
name = gtk_entry_get_text (GTK_ENTRY (entry));
if (gamgi_io_token_double_scan (name, &window_class->rotate_max,
GAMGI_MATH_TOLERANCE_ANGLE, 360.0) == FALSE)
  {
  gamgi_gtk_dialog_message_create ("Error", "Invalid Rotate Parameters", window);
  gamgi_global_remove_window (window_class);
  return;
  }

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_rotate_step");
name = gtk_entry_get_text (GTK_ENTRY (entry));
if (gamgi_io_token_double_scan (name, &window_class->rotate_step,
0.0, window_class->rotate_max) == FALSE)
  {
  gamgi_gtk_dialog_message_create ("Error", "Invalid Rotate Parameters", window);
  gamgi_global_remove_window (window_class);
  return;
  }


entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_move_max");
name = gtk_entry_get_text (GTK_ENTRY (entry));
if (gamgi_io_token_double_scan (name, &window_class->move_max,
GAMGI_MATH_TOLERANCE_LENGTH, DBL_MAX) == FALSE)
  {
  gamgi_gtk_dialog_message_create ("Error", "Invalid Move Parameters", window);
  gamgi_global_remove_window (window_class);
  return;
  }

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_move_step");
name = gtk_entry_get_text (GTK_ENTRY (entry));
if (gamgi_io_token_double_scan (name, &window_class->move_step,
0.0, window_class->move_max) == FALSE)
  {
  gamgi_gtk_dialog_message_create ("Error", "Invalid Move Parameters", window);
  gamgi_global_remove_window (window_class);
  return;
  }


entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_scale_max");
name = gtk_entry_get_text (GTK_ENTRY (entry));
if (gamgi_io_token_double_scan (name, &window_class->scale_max,
1.0 + GAMGI_MATH_TOLERANCE, DBL_MAX) == FALSE)
  {
  gamgi_gtk_dialog_message_create ("Error", "Invalid Scale Parameters", window);
  gamgi_global_remove_window (window_class);
  return;
  }

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_scale_step");
name = gtk_entry_get_text (GTK_ENTRY (entry));
if (gamgi_io_token_double_scan (name, &window_class->scale_step,
0.0, window_class->scale_max - 1.0) == FALSE)
  {
  gamgi_gtk_dialog_message_create ("Error", "Invalid Scale Parameters", window);
  gamgi_global_remove_window (window_class);
  return;
  }


window_class_old = gamgi->window;
gamgi->window = window_class;
gamgi_global_remove_window (window_class_old);


gamgi_gtk_dialog_task0_remove (widget, window);
}
