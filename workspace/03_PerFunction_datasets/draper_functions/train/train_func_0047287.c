static_wyckoff_change (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
GtkWidget *dialog = window->dialog0;
GtkWidget *combo;
GtkWidget *entry;
const char **wyckoff;
const int *driver;
gamgi_bool used[3];
int site;


wyckoff = (const char **) g_object_get_data (G_OBJECT (dialog), "wyckoff");
driver = (const int *) g_object_get_data (G_OBJECT (dialog), "driver");


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_wyckoff");
site = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));


if (wyckoff == NULL || driver == NULL || site == 0)
  { used[0] = TRUE; used[1] = TRUE; used[2] = TRUE; }
else
  gamgi_phys_space_used (wyckoff, driver, site, used);


static_xyz_clean (window);

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_position_x");
if (used[0] == TRUE) gtk_widget_set_sensitive (entry, TRUE);
else gtk_widget_set_sensitive (entry, FALSE);

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_position_y");
if (used[1] == TRUE) gtk_widget_set_sensitive (entry, TRUE);
else gtk_widget_set_sensitive (entry, FALSE);

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_position_z");
if (used[2] == TRUE) gtk_widget_set_sensitive (entry, TRUE);
else gtk_widget_set_sensitive (entry, FALSE);
}
