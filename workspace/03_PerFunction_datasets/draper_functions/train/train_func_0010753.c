static_press (gamgi_object *object, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
gamgi_atom *atom;
GtkWidget *dialog = window->dialog0;
GtkWidget *entry1, *entry2;
char string[2 * GAMGI_ENGINE_TOKEN];
const char *name1, *name2;

atom = GAMGI_CAST_ATOM object;

entry1 = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_atom1");
name1 = gtk_entry_get_text (GTK_ENTRY (entry1));
entry2 = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_atom2");
name2 = gtk_entry_get_text (GTK_ENTRY (entry2));

if (gamgi_io_token_check (name1) == FALSE)
  {
  sprintf (string, "%s %d", atom->object.name, atom->object.number);
  gtk_entry_set_text (GTK_ENTRY (entry1), string);
  }
else
  {
  sprintf (string, "%s %d", atom->object.name, atom->object.number);
  gtk_entry_set_text (GTK_ENTRY (entry2), string);
  }


name1 = gtk_entry_get_text (GTK_ENTRY (entry1));
if (gamgi_io_token_check (name1) == FALSE) return;

name2 = gtk_entry_get_text (GTK_ENTRY (entry2));
if (gamgi_io_token_check (name2) == FALSE) return;

static_ok (NULL, window);
}
