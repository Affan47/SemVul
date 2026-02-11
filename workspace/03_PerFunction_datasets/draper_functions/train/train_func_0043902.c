static_color (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
GtkWidget *dialog = window->dialog0;
GtkWidget *combo;
GtkWidget *entry_red, *entry_green, *entry_blue;
GtkWidget *label_red, *label_green, *label_blue;
int row;

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_color");
row = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));

entry_red = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_red");
entry_green = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_green");
entry_blue = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_blue");
label_red = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "label_red");
label_green = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "label_green");
label_blue = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "label_blue");

if (row == STATIC_COLOR_YES)
  {
  gtk_widget_set_sensitive (entry_red, TRUE);
  gtk_widget_set_sensitive (entry_green, TRUE);
  gtk_widget_set_sensitive (entry_blue, TRUE);
  gtk_widget_set_sensitive (label_red, TRUE);
  gtk_widget_set_sensitive (label_green, TRUE);
  gtk_widget_set_sensitive (label_blue, TRUE);
  }
else
  {
  gtk_entry_set_text (GTK_ENTRY (entry_red), "");
  gtk_entry_set_text (GTK_ENTRY (entry_green), "");
  gtk_entry_set_text (GTK_ENTRY (entry_blue), "");
  gtk_widget_set_sensitive (entry_red, FALSE);
  gtk_widget_set_sensitive (entry_green, FALSE);
  gtk_widget_set_sensitive (entry_blue, FALSE);
  gtk_widget_set_sensitive (label_red, FALSE);
  gtk_widget_set_sensitive (label_green, FALSE);
  gtk_widget_set_sensitive (label_blue, FALSE);
  }
}
