entry_added_one (GkmGnome2File *df, const gchar *identifier, gboolean *added)
{
	g_assert (GKM_IS_GNOME2_FILE (df));
	g_assert (identifier);
	g_assert (added);


	g_assert (!*added);
	*added = TRUE;
}
