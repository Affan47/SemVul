download_detect_tls_support(struct download *d, header_t *header)
{
	download_check(d);
	dl_server_valid(d->server);

	if (d->got_giv)
		return;

	if (
		header_get_feature("tls", header, NULL, NULL) ||
		xalt_detect_tls_support(d, header)
	) {
		tls_cache_insert(download_addr(d), download_port(d));
		d->server->attrs |= DLS_A_TLS;
	}
}
