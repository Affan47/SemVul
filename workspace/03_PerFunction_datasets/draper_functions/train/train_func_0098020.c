do_info (gint argc,
         gchar **argv)
{
	gint i;
	CamelIndex *idx;

	for (i = 2; i < argc; i++) {
		printf ("Opening index file: %s\n", argv[i]);
		idx = (CamelIndex *) camel_text_index_new (argv[i], O_RDONLY);
		if (idx) {
			camel_text_index_info ((CamelTextIndex *) idx);
			g_object_unref (idx);
		} else {
			printf (" Failed: %s\n", g_strerror (errno));
			return 0;
		}
	}
	return 1;
}
