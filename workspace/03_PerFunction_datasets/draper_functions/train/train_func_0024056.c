camel_nntp_stream_line (CamelNNTPStream *is,
                        guchar **data,
                        guint *len,
                        GCancellable *cancellable,
                        GError **error)
{
	register guchar c, *p, *o, *oe;
	gint newlen, oldlen;
	guchar *e;

	g_return_val_if_fail (is != NULL, -1);
	g_return_val_if_fail (data != NULL, -1);
	g_return_val_if_fail (len != NULL, -1);

	if (is->mode == CAMEL_NNTP_STREAM_EOD) {
		*data = is->linebuf;
		*len = 0;
		return 0;
	}

	o = is->linebuf;
	oe = is->lineend - 1;
	p = is->ptr;
	e = is->end;


	if (is->mode == CAMEL_NNTP_STREAM_DATA) {

		while (e - p < 3) {
			is->ptr = p;
			if (nntp_stream_fill (is, cancellable, error) == -1)
				return -1;
			p = is->ptr;
			e = is->end;
		}


		if (p[0] == '.') {
			if (p[1] == '\r' && p[2] == '\n') {
				is->ptr = p + 3;
				is->mode = CAMEL_NNTP_STREAM_EOD;
				*data = is->linebuf;
				*len = 0;
				is->linebuf[0] = 0;

				dd (printf ("NNTP_STREAM_LINE (END)\n"));

				return 0;
			}
			p++;
		}
	}

	while (1) {
		while (o < oe) {
			c = *p++;
			if (c == '\n') {

				if (p> e) {
					is->ptr = e;
					if (nntp_stream_fill (is, cancellable, error) == -1)
						return -1;
					p = is->ptr;
					e = is->end;
				} else {
					is->ptr = p;
					*data = is->linebuf;
					*len = o - is->linebuf;
					*o = 0;

					dd (printf ("NNTP_STREAM_LINE (%d): '%s'\n", *len, *data));

					return 1;
				}
			} else if (c != '\r') {
				*o++ = c;
			}
		}


		oldlen = o - is->linebuf;
		newlen = (is->lineend - is->linebuf) * 3 / 2;
		is->lineptr = is->linebuf = g_realloc (is->linebuf, newlen);
		is->lineend = is->linebuf + newlen;
		oe = is->lineend - 1;
		o = is->linebuf + oldlen;
	}
}
