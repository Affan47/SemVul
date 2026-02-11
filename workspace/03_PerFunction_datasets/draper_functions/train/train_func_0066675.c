gsearchtool_get_unique_filename (const gchar * path,
                                 const gchar * suffix)
{
	const gint num_of_words = 12;
	gchar     * words[] = {
		    "foo",
		    "bar",
		    "blah",
	   	    "cranston",
		    "frobate",
		    "hadjaha",
		    "greasy",
		    "hammer",
		    "eek",
		    "larry",
		    "curly",
		    "moe",
		    NULL};
	gchar * retval = NULL;
	gboolean exists = TRUE;

	while (exists) {
		gchar * file;
		gint rnd;
		gint word;

		rnd = rand ();
		word = rand () % num_of_words;

		file = g_strdup_printf ("%s-%010x%s",
					    words [word],
					    (guint) rnd,
					    suffix);

		g_free (retval);
		retval = g_strconcat (path, G_DIR_SEPARATOR_S, file, NULL);
		exists = g_file_test (retval, G_FILE_TEST_EXISTS);
		g_free (file);
	}
	return retval;
}
