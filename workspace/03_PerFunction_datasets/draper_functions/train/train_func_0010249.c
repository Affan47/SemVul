vfp_testgzip_bytes(struct sess *sp, struct http_conn *htc, ssize_t bytes)
{
	struct vgz *vg;
	ssize_t l, w;
	int i = -100;
	uint8_t	obuf[params->gzip_stack_buffer];
	size_t dl;
	const void *dp;
	struct storage *st;

	vg = sp->wrk->vgz_rx;
	CHECK_OBJ_NOTNULL(vg, VGZ_MAGIC);
	AZ(vg->vz.avail_in);
	while (bytes > 0) {
		st = FetchStorage(sp, 0);
		if (st == NULL)
			return (-1);
		l = st->space - st->len;
		if (l > bytes)
			l = bytes;
		w = HTC_Read(htc, st->ptr + st->len, l);
		if (w <= 0)
			return (w);
		bytes -= w;
		VGZ_Ibuf(vg, st->ptr + st->len, w);
		st->len += w;
		sp->obj->len += w;
		if (sp->wrk->do_stream)
			RES_StreamPoll(sp);

		while (!VGZ_IbufEmpty(vg)) {
			VGZ_Obuf(vg, obuf, sizeof obuf);
			i = VGZ_Gunzip(vg, &dp, &dl);
			if (i == VGZ_END && !VGZ_IbufEmpty(vg)) {
				WSP(sp, SLT_FetchError, "Junk after gzip data");
				return (-1);
			}
			if (i != VGZ_OK && i != VGZ_END) {
				WSP(sp, SLT_FetchError,
				    "Invalid Gzip data: %s", vg->vz.msg);
				return (-1);
			}
		}
	}
	if (i == VGZ_OK || i == VGZ_END)
		return (1);
	WSP(sp, SLT_FetchError, "Gunzip trouble (%d)", i);
	return (-1);
}
