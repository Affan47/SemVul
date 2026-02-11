upload_thex_uri_add(char *buf, size_t size, void *arg, uint32 flags)
{
	struct upload_http_cb *a = arg;
	struct upload *u = a->u;
	const struct sha1 *sha1;
	const struct tth *tth;
	size_t len = 0;

	upload_check(u);

	g_return_val_if_fail(u->sf, 0);
	shared_file_check(u->sf);

	sha1 = shared_file_sha1(u->sf);
	g_return_val_if_fail(sha1, 0);

	if ((flags & HTTP_CBF_BW_SATURATED) && u->n2r)
		return 0;

	tth = shared_file_tth(u->sf);
	if (!tth)
		return 0;

	len = concat_strings(buf, size,
			"X-Thex-URI: /uri-res/N2X?", sha1_to_urn_string(sha1),
			";", tth_base32(tth),
			"\r\n",
			(void *) 0);

	if (len >= size && GNET_PROPERTY(upload_debug)) {
		g_warning("U/L cannot send X-Thex-URI header back: only %u byte%s left",
			(unsigned) size, 1 == size ? "" : "s");
	}

	return len < size ? len : 0;
}
