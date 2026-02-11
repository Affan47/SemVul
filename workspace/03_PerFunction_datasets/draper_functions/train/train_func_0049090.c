search_results_set_auto_download(gnet_results_set_t *rs)
{
	const GSList *sl;

	if (!GNET_PROPERTY(auto_download_identical))
		return;

	for (sl = rs->records; sl; sl = g_slist_next(sl)) {
		gnet_record_t *rc = sl->data;
		fileinfo_t *fi;

		if (!rc->sha1)
			continue;

		fi = file_info_has_identical(rc->sha1, rc->size);
		if (fi) {
			uint32 flags = 0;

			flags |= (rs->status & ST_FIREWALL) ? SOCK_F_PUSH : 0;
			flags |= !host_is_valid(rs->addr, rs->port) ? SOCK_F_PUSH : 0;
			flags |= (rs->status & ST_TLS) ? SOCK_F_TLS : 0;

			download_auto_new(rc->filename,
				rc->size,
				rs->addr,
				rs->port,
				rs->guid,
				rs->hostname,
				rc->sha1,
				rc->tth,
				rs->stamp,
				fi,
				rs->proxies,
				flags);

			search_free_proxies(rs);
			rc->flags |= SR_DOWNLOADED;


			if (rc->alt_locs != NULL)
				search_check_alt_locs(rs, rc, fi);

			g_assert(rc->alt_locs == NULL);
		}
	}
}
