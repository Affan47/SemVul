do_dump (gint argc,
         gchar **argv)
{
	gint i;
	CamelIndex *idx;

	for (i = 2; i < argc; i++) {
		printf ("Opening index file: %s\n", argv[i]);
		idx = (CamelIndex *) camel_text_index_new (argv[i], O_RDONLY);
		if (idx) {
			printf (" Dumping ...\n");
			camel_text_index_dump ((CamelTextIndex *) idx);
			g_object_unref (idx);
		} else {
			printf (" Failed: %s\n", g_strerror (errno));
			return 1;
		}
	}
	return 0;
}
