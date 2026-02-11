static_nodes (gamgi_cell *cell, gamgi_window *window)
{
GtkWidget *dialog = window->dialog0;
GtkWidget *combo;
int lattice, vectors;
int row;


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_o4");
gtk_combo_box_set_active (GTK_COMBO_BOX (combo), 7);


if (cell == NULL) lattice = 0;
else lattice = cell->lattice;


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_vectors");
row = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));

if (row == STATIC_VECTORS_PRIMITIVE) vectors = GAMGI_PHYS_PRIMITIVE;
else vectors = GAMGI_PHYS_CONVENTIONAL;


gamgi_gtk_cell_symmetry_nodes (lattice, vectors, dialog);
}
