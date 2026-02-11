vfp_esi_bytes_ug(struct worker *wrk, struct http_conn *htc, ssize_t bytes)
{
	ssize_t wl;
	char ibuf[cache_param->gzip_stack_buffer];
	struct vef_priv *vef;

	CHECK_OBJ_NOTNULL(wrk, WORKER_MAGIC);
	CHECK_OBJ_NOTNULL(wrk->busyobj, BUSYOBJ_MAGIC);
	vef = wrk->busyobj->vef_priv;
	CHECK_OBJ_NOTNULL(vef, VEF_MAGIC);

	while (bytes > 0) {
		wl = vef_read(wrk, htc, ibuf, sizeof ibuf, bytes);
		if (wl <= 0)
			return (wl);
		bytes -= wl;
		vef->bufp = ibuf;
		VEP_Parse(wrk, ibuf, wl);
		assert(vef->bufp >= ibuf && vef->bufp <= ibuf + wl);
		if (vef->error) {
			errno = vef->error;
			return (-1);
		}
		if (vef->bufp < ibuf + wl) {
			wl = (ibuf + wl) - vef->bufp;
			assert(wl + vef->npend < sizeof vef->pending);
			memmove(vef->pending + vef->npend, vef->bufp, wl);
			vef->npend += wl;
		}
	}
	return (1);
}
