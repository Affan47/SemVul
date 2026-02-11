static_start_scope (gamgi_window *window)
{
GtkWidget *dialog = window->dialog0;
GtkWidget *combo;
GtkWidget *entry;
GtkWidget *button_cell;
GtkWidget *button_range;
GtkWidget *button_node;
char token[GAMGI_ENGINE_TOKEN];
gamgi_bool active;


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_structure");
gtk_combo_box_set_active (GTK_COMBO_BOX (combo), GAMGI_CHEM_STRUCTURE - 1);

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_filter");
gtk_combo_box_set_active (GTK_COMBO_BOX (combo), GAMGI_CHEM_FILTER - 1);

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_thickness");
sprintf (token, "%.*f", gamgi->gamgi->length, GAMGI_CHEM_DIRECTION_THICKNESS);
gtk_entry_set_text (GTK_ENTRY (entry), token);


button_cell = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "button_cell");
button_range = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "button_range");
button_node = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "button_node");

if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button_node)) == FALSE)
  gtk_button_clicked (GTK_BUTTON (button_node));

active = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button_cell));
if (active == TRUE)
  {
  gtk_widget_set_sensitive (button_range, TRUE);
  gtk_widget_set_sensitive (button_node, TRUE);
  }
else
  {
  gtk_widget_set_sensitive (button_range, FALSE);
  gtk_widget_set_sensitive (button_node, FALSE);
  }

gamgi_gtk_direction_create_node (active, window);


static_instance (NULL, window);
}
