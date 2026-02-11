addto_slist_cb (gpointer ref,
                gint col,
                gchar **cols,
                gchar **name)
{
	GSList **uids = ref;

	if (cols[0])
		*uids = g_slist_prepend (*uids, g_strdup (cols [0]));

	return 0;
}
