search_ggep_write(ggep_stream_t *gs, const extvec_t *e, const char *id,
	const void *payload, size_t plen,
	const gnutella_node_t *n, const char *caller)
{
	uint32 flags;
	bool ok;
	const char *extid;

	g_assert((NULL == e) ^ (NULL == id));

	if (e != NULL) {
		flags = (plen > DEFLATE_THRESHOLD || ext_ggep_is_deflated(e)) ?
			GGEP_W_DEFLATE : 0;
		extid = ext_ggep_id_str(e);
	} else {
		flags = plen > DEFLATE_THRESHOLD ? GGEP_W_DEFLATE : 0;
		extid = id;
	}

	ok = ggep_stream_pack(gs, extid, payload, plen, flags);

	if (!ok)
		search_log_ggep_write_failure(extid, flags, n, caller);
}
