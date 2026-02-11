check_streams_match (GMimeStream *orig, GMimeStream *dup, const char *filename, int check_overflow)
{
	char buf[4096], dbuf[4096], errstr[1024];
	gint64 len, totalsize, totalread = 0;
	size_t nread, size;
	ssize_t n;

	v(fprintf (stdout, "Matching original stream (%" G_GINT64_FORMAT " -> %" G_GINT64_FORMAT ") with %s (%" G_GINT64_FORMAT ", %" G_GINT64_FORMAT ")... ",
		   orig->position, orig->bound_end, filename, dup->position, dup->bound_end));

	if (orig->bound_end != -1) {
		totalsize = orig->bound_end - orig->position;
	} else if ((len = g_mime_stream_length (orig)) == -1) {
		sprintf (errstr, "Error: Unable to get length of original stream\n");
		goto fail;
	} else if (len < (orig->position - orig->bound_start)) {
		sprintf (errstr, "Error: Overflow on original stream?\n");
		goto fail;
	} else {
		totalsize = len - (orig->position - orig->bound_start);
	}

	while (totalread < totalsize) {
		if ((n = g_mime_stream_read (orig, buf, sizeof (buf))) <= 0)
			break;

		size = n;
		nread = 0;
		totalread += n;

		d(fprintf (stderr, "read %zu bytes from original stream\n", size));

		do {
			if ((n = g_mime_stream_read (dup, dbuf + nread, size - nread)) <= 0) {
				d(fprintf (stderr, "dup read() returned %zd, EOF\n", n));
				break;
			}
			d(fprintf (stderr, "read %zd bytes from dup stream\n", n));
			nread += n;
		} while (nread < size);

		if (nread < size) {
			sprintf (errstr, "Error: `%s' appears to be truncated, short %zu+ bytes\n",
				 filename, size - nread);
			goto fail;
		}

		if (memcmp (buf, dbuf, size) != 0) {
			sprintf (errstr, "Error: `%s': content does not match\n", filename);
			goto fail;
		} else {
			d(fprintf (stderr, "%zu bytes identical\n", size));
		}
	}

	if (totalread < totalsize) {
		sprintf (errstr, "Error: expected more data from original stream\n");
		goto fail;
	}

	if (check_overflow && (n = g_mime_stream_read (dup, buf, sizeof (buf))) > 0) {
		sprintf (errstr, "Error: `%s' appears to contain extra content\n", filename);
		goto fail;
	}

	v(fputs ("passed\n", stdout));

	return 0;

 fail:

	v(fputs ("failed\n", stdout));
	v(fputs (errstr, stderr));

	return -1;
}
