xpm_read_string (FILE *infile, gchar **buffer, guint *buffer_size)
{
	gint c;
	guint cnt = 0, bufsiz, ret = FALSE;
	gchar *buf;

	buf = *buffer;
	bufsiz = *buffer_size;
	if (buf == NULL) {
		bufsiz = 10 * sizeof (gchar);
		buf = g_new (gchar, bufsiz);
	}

	do {
		c = getc (infile);
	} while (c != EOF && c != '"');

	if (c != '"')
		goto out;

	while ((c = getc (infile)) != EOF) {
		if (cnt == bufsiz) {
			guint new_size = bufsiz * 2;

			if (new_size > bufsiz)
				bufsiz = new_size;
			else
				goto out;

			buf = g_realloc (buf, bufsiz);
			buf[bufsiz - 1] = '\0';
		}

		if (c != '"')
			buf[cnt++] = c;
		else {
			buf[cnt] = 0;
			ret = TRUE;
			break;
		}
	}

 out:
	buf[bufsiz - 1] = '\0';
	*buffer = buf;
	*buffer_size = bufsiz;
	return ret;
}
