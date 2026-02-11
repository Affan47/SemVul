static_name (gamgi_window *window, char *name)
{
gamgi_plane *plane;
GtkWidget *dialog = window->dialog0;
GtkWidget *entry;
GtkWidget *button;
char string[GAMGI_ENGINE_STRING];
int active;

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_plane");

plane = GAMGI_CAST_PLANE gamgi_gtk_object_number (dialog,
"entry_plane", GAMGI_ENGINE_PLANE, window, string);

button = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "button_list");
active = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button));

if (active == TRUE || plane == NULL)
  {
  sprintf (string, "%s", name);
  }
else
  {
  if (strcmp (name, "") == 0)
    sprintf (string, "%s %d", plane->object.name, plane->object.number);
  else
    sprintf (string, "%s %d", name, plane->object.number);
  }

gtk_entry_set_text (GTK_ENTRY (entry), string);
}
