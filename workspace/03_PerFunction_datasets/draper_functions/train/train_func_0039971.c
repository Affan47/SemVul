load_mime_types(void)
{
    static char	*buffer = NULL;
    char	*c;
    long	n_alloc;

    n_types = 0;
    if (global.mime_types) {
	int	fd = open(global.mime_types, O_RDONLY);

	if (fd < 0)
	    perror(global.mime_types);
	else {
	    buffer = snarf_file(fd, NULL);
	    close(fd);
	}
    }

    n_alloc = 8;
    mime_types = (MimeType *)XtMalloc(n_alloc * sizeof mime_types[0]);

    c = buffer;
    while (c) {
	char	*end = strchr(c, '\n');
	char	*type, *suffix;

	if (end)
	    *end++ = '\0';
	type = strtok(c, " \t");
	if (type)
	    while ((suffix = strtok(NULL, " \t"))) {
		if (n_types + 8 > n_alloc) {
		    n_alloc = 2 * (n_types + 8);
		    mime_types =
			(MimeType *)XtRealloc((char *)mime_types,
					      n_alloc * sizeof mime_types[0]);
		}
		ascii_lower(suffix);
		mime_types[n_types].type   = type;
		mime_types[n_types].suffix = suffix;
		n_types++;
	    }

	c = end;
    }

    mime_types[n_types].type   = "image/jpeg";
    mime_types[n_types].suffix = "jpeg";
    n_types++;
    mime_types[n_types].type   = "image/jpeg";
    mime_types[n_types].suffix = "jpg";
    n_types++;
    mime_types[n_types].type   = "image/gif";
    mime_types[n_types].suffix = "gif";
    n_types++;
    mime_types[n_types].type   = "image/png";
    mime_types[n_types].suffix = "png";
    n_types++;
    mime_types[n_types].type   = "application/postscript";
    mime_types[n_types].suffix = "ps";
    n_types++;

    mime_types = (MimeType *)XtRealloc((char *)mime_types,
				       n_types * sizeof mime_types[0]);
}
