file_info_add_source(fileinfo_t *fi, struct download *d)
{
	file_info_check(fi);
	g_assert(NULL == d->file_info);
	g_assert(!d->src_handle_valid);

	fi->refcount++;
	fi->dirty_status = TRUE;
	d->file_info = fi;
	d->src_handle = idtable_new_id(src_handle_map, d);
	d->src_handle_valid = TRUE;
	fi->sources = g_slist_prepend(fi->sources, d);

	if (download_is_alive(d)) {
		g_assert(fi->refcount > fi->lifecount);
		fi->lifecount++;
	}

	if (1 == fi->refcount) {
		g_assert(GNET_PROPERTY(fi_with_source_count)
				< GNET_PROPERTY(fi_all_count));
		gnet_prop_incr_guint32(PROP_FI_WITH_SOURCE_COUNT);
	}

	src_event_trigger(d, EV_SRC_ADDED);


}
