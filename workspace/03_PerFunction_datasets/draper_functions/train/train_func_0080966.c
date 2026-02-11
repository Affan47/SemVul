gamgi_gtk_select_combo_int (int *min, int *max, gamgi_window *window)
{
GtkWidget *dialog = window->dialog0;
GtkWidget *combo;
int swap;


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "widget_min");
*min = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "widget_max");
*max = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));

if (*min > *max)
  {
  gamgi_gtk_dialog_message_create ("Warning", "Swapped range limits", window);

  swap = *min;
  *min = *max;
  *max = swap;
  }

}
