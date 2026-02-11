gal_view_generate_id (GalViewCollection *collection,
                      GalView *view)
{
	gint i;
	for (i = 1; TRUE; i++) {
		gchar *try;

		try = gal_view_generate_string (collection, view, i);
		if (gal_view_check_string (collection, try))
			return try;
		g_free (try);
	}
}
