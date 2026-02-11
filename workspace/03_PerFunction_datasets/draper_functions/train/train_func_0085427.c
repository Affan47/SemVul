dmesh_multiple_downloads(const struct sha1 *sha1,
	filesize_t size, fileinfo_t *fi)
{
	dmesh_urlinfo_t buffer[DMESH_MAX], *p;
	int n;
	time_t now;

	n = dmesh_alt_loc_fill(sha1, buffer, DMESH_MAX);
	if (n == 0)
		return;

	now = tm_time();

	for (p = buffer; n > 0; n--, p++) {
		const char *filename;

		if (GNET_PROPERTY(dmesh_debug) > 2)
			g_debug("ALT-LOC queuing from MESH: %s",
				dmesh_urlinfo_to_string(p));

		filename = URN_INDEX == p->idx && fi
			? filepath_basename(fi->pathname) : p->name;
		download_auto_new(filename,
			size,
			p->addr,
			p->port,
			&blank_guid,
			NULL,
			sha1,
			NULL,
			now,
			fi,
			NULL,
			0);
	}
}
