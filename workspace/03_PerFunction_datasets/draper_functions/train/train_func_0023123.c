static_nodes (gamgi_window *window)
{
GtkWidget *dialog = window->dialog0;
GtkWidget *combo;
gamgi_enum lattice, vectors;
int row;


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_o4");
gtk_combo_box_set_active (GTK_COMBO_BOX (combo), 0);


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_origin_vectors");
row = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));

if (row == GAMGI_PHYS_PRIMITIVE - 1) vectors = GAMGI_PHYS_PRIMITIVE;
else vectors = GAMGI_PHYS_CONVENTIONAL;

lattice = gamgi_gtk_cell_symmetry_lattice (dialog);
gamgi_gtk_cell_symmetry_nodes (lattice, vectors, dialog);
}
