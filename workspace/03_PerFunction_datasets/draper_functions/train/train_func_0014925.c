download_pick_followup(struct download *d, const struct sha1 *sha1)
{
	list_iter_t *iter;
	bool was_plain_incomplete;
	bool found = FALSE;

	download_check(d);
	g_assert(d->list_idx == DL_LIST_WAITING);
	g_assert(!download_pipelining(d));

	if (!GNET_PROPERTY(dl_resource_switching))
		return d;


	if (is_strprefix(download_vendor_str(d), "gtk-gnutella/")) {
		version_t ver;

		if (!version_fill(download_vendor_str(d), &ver) || ver.build < 14884)
			return d;


	}


	was_plain_incomplete = !FILE_INFO_COMPLETE(d->file_info) &&
		!download_is_special(d);


	if (was_plain_incomplete) {
		struct guid *id = dualhash_lookup_key(dl_thex, d->id);


		if (id != NULL) {
			struct download *dt = hikset_lookup(dl_by_id, id);

			download_check(dt);
			g_assert(dt->flags & DL_F_THEX);

			if (DOWNLOAD_IS_SWITCHABLE(dt)) {
				if (GNET_PROPERTY(download_debug)) {
					g_debug("TTH requesting switching from "
						"plain \"%s\" to \"%s\" on %s",
						download_basename(d), download_basename(dt),
						download_host_info(d));
				}
				d = dt;
				goto done;
			}
		}
	}


	iter = list_iter_before_head(d->server->list[DL_LIST_RUNNING]);
	while (list_iter_has_next(iter)) {
		struct download *cur;

		cur = list_iter_next(iter);
		download_check(cur);

		if (download_pick_process(&d, cur, was_plain_incomplete, sha1, FALSE)) {
			found = TRUE;
			break;
		}
	}
	list_iter_free(&iter);

	if (found)
		goto done;

	iter = list_iter_before_head(d->server->list[DL_LIST_WAITING]);
	while (list_iter_has_next(iter)) {
		struct download *cur;

		cur = list_iter_next(iter);
		download_check(cur);

		if (download_pick_process(&d, cur, was_plain_incomplete, sha1, FALSE))
			break;
	}
	list_iter_free(&iter);

done:


	if (d->list_idx == DL_LIST_RUNNING)
		download_stop(d, GTA_DL_TIMEOUT_WAIT, no_reason);

	g_assert(d->list_idx == DL_LIST_WAITING);

	return d;
}
