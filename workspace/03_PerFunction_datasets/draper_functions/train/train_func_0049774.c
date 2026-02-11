static_init (gamgi_window *window)
{
gamgi_bond_class *bond_class = gamgi->bond;
GtkWidget *dialog = window->dialog0;
GtkWidget *entry;
GtkWidget *combo;
GtkWidget *button;
char token[GAMGI_ENGINE_TOKEN];


entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_lower");
sprintf (token, "%.*f", GAMGI_MATH_DECIMAL_SCALE, bond_class->lower);
gtk_entry_set_text (GTK_ENTRY (entry), token);

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_upper");
sprintf (token, "%.*f", GAMGI_MATH_DECIMAL_SCALE, bond_class->upper);
gtk_entry_set_text (GTK_ENTRY (entry), token);


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_style");
if (bond_class->draw == gamgi_mesa_bond_draw_line)
  gtk_combo_box_set_active (GTK_COMBO_BOX (combo), GAMGI_MESA_WIRED - 1);
if (bond_class->draw == gamgi_mesa_bond_draw_cylinder)
  gtk_combo_box_set_active (GTK_COMBO_BOX (combo), GAMGI_MESA_SOLID - 1);


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_size");
sprintf (token, "%.*f", GAMGI_MATH_DECIMAL_SIZE, bond_class->size);
entry = gtk_bin_get_child (GTK_BIN (combo));
gtk_entry_set_text (GTK_ENTRY (entry), token);


button = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "button_color");
if (bond_class->color == TRUE)
  gtk_button_clicked (GTK_BUTTON (button));


entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_red");
sprintf (token, "%.*f", GAMGI_MATH_DECIMAL_COLOR, bond_class->red);
gtk_entry_set_text (GTK_ENTRY (entry), token);

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_green");
sprintf (token, "%.*f", GAMGI_MATH_DECIMAL_COLOR, bond_class->green);
gtk_entry_set_text (GTK_ENTRY (entry), token);

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_blue");
sprintf (token, "%.*f", GAMGI_MATH_DECIMAL_COLOR, bond_class->blue);
gtk_entry_set_text (GTK_ENTRY (entry), token);
}
