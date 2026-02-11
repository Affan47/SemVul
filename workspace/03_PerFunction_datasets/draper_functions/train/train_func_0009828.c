static_default (int number, char *name, gamgi_window *window)
{
GtkWidget *dialog = window->dialog0;
GtkWidget *entry_atom, *entry_label;
GtkWidget *entry_mass, *entry_radius, *entry_charge;
GtkWidget *entry_red, *entry_green, *entry_blue;
char token[GAMGI_ENGINE_TOKEN];
const char *input;

entry_atom = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_atom");
input = gtk_entry_get_text (GTK_ENTRY (entry_atom));
entry_label = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_label");

entry_mass = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_mass");
entry_radius = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_radius");
entry_charge = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_charge");

entry_red = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_red");
entry_green = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_green");
entry_blue = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_blue");

if (number >= 0)
  {


  static_name (window, name);
  gamgi_io_token_lower (name, token);
  gtk_entry_set_text (GTK_ENTRY (entry_label), token);


  sprintf (token, "%.*f", gamgi->gamgi->mass, gamgi->atom->mass[number]);
  gtk_entry_set_text (GTK_ENTRY (entry_mass), token);

  sprintf (token, "%.*f", gamgi->gamgi->length, gamgi->atom->radius[number]);
  gtk_entry_set_text (GTK_ENTRY (entry_radius), token);

  sprintf (token, "%.*f", gamgi->gamgi->charge, 0.0);
  gtk_entry_set_text (GTK_ENTRY (entry_charge), token);


  sprintf (token, "%.*f", GAMGI_MATH_DECIMAL_COLOR, gamgi->atom->red[number]);
  gtk_entry_set_text (GTK_ENTRY (entry_red), token);
  sprintf (token, "%.*f", GAMGI_MATH_DECIMAL_COLOR, gamgi->atom->green[number]);
  gtk_entry_set_text (GTK_ENTRY (entry_green), token);
  sprintf (token, "%.*f", GAMGI_MATH_DECIMAL_COLOR, gamgi->atom->blue[number]);
  gtk_entry_set_text (GTK_ENTRY (entry_blue), token);
  }
else
  {


  static_name (window, NULL);
  gtk_entry_set_text (GTK_ENTRY (entry_label), "");

  gtk_entry_set_text (GTK_ENTRY (entry_mass), "");
  gtk_entry_set_text (GTK_ENTRY (entry_radius), "");
  gtk_entry_set_text (GTK_ENTRY (entry_charge), "");

  gtk_entry_set_text (GTK_ENTRY (entry_red), "");
  gtk_entry_set_text (GTK_ENTRY (entry_green), "");
  gtk_entry_set_text (GTK_ENTRY (entry_blue), "");
  }

}
