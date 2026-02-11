static_list (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
GtkWidget *dialog = window->dialog0;
GtkWidget *button;
GtkWidget *hbox;

hbox = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "hbox_layer");
button = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "button_list");

if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button)) == FALSE)
  {


  gtk_widget_set_sensitive (hbox, TRUE);
  static_default_layer (window);
  }
else
  {


  static_reset (window);
  gtk_widget_set_sensitive (hbox, FALSE);
  }

static_reference (NULL, window);
}
