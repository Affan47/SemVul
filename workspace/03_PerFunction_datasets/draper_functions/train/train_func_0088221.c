file_info_cloned_source(fileinfo_t *fi, download_t *d, download_t *cd)
{
	file_info_check(fi);
	g_assert(NULL != d->file_info);
	g_assert(cd->src_handle_valid);
	g_assert(fi->refcount > 0);
	g_assert(fi->refcount >= fi->lifecount);
	g_assert(fi->hashed);

	cd->src_handle = idtable_new_id(src_handle_map, cd);
	fi->sources = g_slist_prepend(fi->sources, cd);
	src_event_trigger(cd, EV_SRC_ADDED);


	fi->refcount++;
	if (download_is_alive(d)) {
		g_assert(fi->refcount > fi->lifecount);
		fi->lifecount++;
	}
}
