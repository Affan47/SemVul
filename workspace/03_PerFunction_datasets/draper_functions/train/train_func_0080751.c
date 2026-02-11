pgx_gethdr(jas_stream_t *in, pgx_hdr_t *hdr)
{
	int c;
	uchar buf[2];

	if ((c = jas_stream_getc(in)) == EOF) {
		goto error;
	}
	buf[0] = c;
	if ((c = jas_stream_getc(in)) == EOF) {
		goto error;
	}
	buf[1] = c;
	hdr->magic = buf[0] << 8 | buf[1];
	if (hdr->magic != PGX_MAGIC) {
		goto error;
	}
	if ((c = pgx_getc(in)) == EOF || !isspace(c)) {
		goto error;
	}
	if (pgx_getbyteorder(in, &hdr->bigendian)) {
		goto error;
	}
	if (pgx_getsgnd(in, &hdr->sgnd)) {
		goto error;
	}
	if (pgx_getuint32(in, &hdr->prec)) {
		goto error;
	}
	if (pgx_getuint32(in, &hdr->width)) {
		goto error;
	}
	if (pgx_getuint32(in, &hdr->height)) {
		goto error;
	}
	return 0;

error:
	return -1;
}
