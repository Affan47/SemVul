gbemol_preferences_load_entry(GtkWidget* entry, gchar* group, gchar* key)
{
	gchar *txt;
	if ((txt = gbemol_cfg_get_string(group, key))) {
		gtk_entry_set_text(GTK_ENTRY(entry), txt);
		g_free(txt);
	}
}
