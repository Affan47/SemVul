uuencode (const char *progname, int argc, char **argv)
{
	GMimeStream *istream, *ostream, *fstream;
	GMimeContentEncoding encoding;
	const char *filename, *name;
	GMimeFilter *filter;
	gboolean base64;
	struct stat st;
	int fd, opt;

	base64 = FALSE;
	encoding = GMIME_CONTENT_ENCODING_UUENCODE;
	while ((opt = getopt_long (argc, argv, "hvm", longopts, NULL)) != -1) {
		switch (opt) {
		case 'h':
			usage (progname);
			return 0;
		case 'v':
			version (progname);
			return 0;
		case 'm':
			base64 = TRUE;
			encoding = GMIME_CONTENT_ENCODING_BASE64;
			break;
		default:
			printf ("Try `%s --help' for more information.\n", progname);
			return -1;
		}
	}

	if (optind >= argc) {
		printf ("Try `%s --help' for more information.\n", progname);
		return -1;
	}

	if (optind + 1 < argc)
		filename = argv[optind++];
	else
		filename = NULL;

	name = argv[optind];


	if ((fd = filename ? open (filename, O_RDONLY, 0) : dup (0)) == -1) {
		fprintf (stderr, "%s: %s: %s\n", progname,
			 filename ? filename : "stdin",
			 g_strerror (errno));
		return -1;
	}


	if (fstat (fd, &st) == -1) {
		fprintf (stderr, "%s: %s: %s\n", progname,
			 filename ? filename : "stdin",
			 g_strerror (errno));
		close (fd);
		return -1;
	}

	printf ("begin%s %.3o %s\n", base64 ? "-base64" : "", st.st_mode & 0777, name);
	fflush (stdout);

	istream = g_mime_stream_fs_new (fd);


	ostream = g_mime_stream_fs_new (1);
	g_mime_stream_fs_set_owner ((GMimeStreamFs *) ostream, FALSE);

	fstream = g_mime_stream_filter_new (ostream);


	filter = g_mime_filter_basic_new (encoding, TRUE);
	g_mime_stream_filter_add ((GMimeStreamFilter *) fstream, filter);
	g_object_unref (filter);

	if (g_mime_stream_write_to_stream (istream, fstream) == -1) {
		fprintf (stderr, "%s: %s\n", progname, g_strerror (errno));
		g_object_unref (fstream);
		g_object_unref (istream);
		g_object_unref (ostream);
		return -1;
	}

	g_mime_stream_flush (fstream);
	g_object_unref (fstream);
	g_object_unref (istream);

	if (g_mime_stream_write_string (ostream, base64 ? "====\n" : "end\n") == -1) {
		fprintf (stderr, "%s: %s\n", progname, g_strerror (errno));
		g_object_unref (ostream);
		return -1;
	}

	g_object_unref (ostream);

	return 0;
}
