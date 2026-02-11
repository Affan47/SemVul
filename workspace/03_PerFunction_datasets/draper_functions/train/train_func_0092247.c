gui_defect_neutralization(GtkWidget *entry)
{
const gchar *text;

g_assert(entry != NULL);
g_assert(GTK_IS_ENTRY(entry));

text = gtk_entry_get_text(GTK_ENTRY(entry));
}
