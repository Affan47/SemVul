static_start_cell (gamgi_window *window)
{
GtkWidget *dialog = window->dialog0;
GtkWidget *entry;
GtkWidget *combo;
int row;

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_cell");
gtk_entry_set_text (GTK_ENTRY (entry), "");

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_u");
gtk_entry_set_text (GTK_ENTRY (entry), "");
entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_v");
gtk_entry_set_text (GTK_ENTRY (entry), "");
entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_w");
gtk_entry_set_text (GTK_ENTRY (entry), "");

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_reference");
row = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));
if (row == STATIC_REFERENCE_CELL)
  {
  combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_vectors");
  gtk_combo_box_set_active (GTK_COMBO_BOX (combo), GAMGI_PHYS_DIRECTION_VECTORS - 1);
  }
else
  {
  combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_vectors");
  gtk_combo_box_set_active (GTK_COMBO_BOX (combo), STATIC_VECTORS_LOCAL);
  }
}
