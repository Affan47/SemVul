pgx_puthdr(jas_stream_t *out, pgx_hdr_t *hdr)
{
	jas_stream_printf(out, "%c%c", hdr->magic >> 8, hdr->magic & 0xff);
	jas_stream_printf(out, " %s %s %d %ld %ld\n", hdr->bigendian ? "ML" : "LM",
	  hdr->sgnd ? "-" : "+", hdr->prec, (long) hdr->width, (long) hdr->height);
	if (jas_stream_error(out)) {
		return -1;
	}
	return 0;
}
