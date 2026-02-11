download_convert_to_urires(struct download *d)
{
	struct download *xd;

	download_check(d);
	g_assert(d->uri == NULL);
	g_assert(d->record_index != URN_INDEX);
	g_assert(d->sha1 != NULL);
	g_assert(d->file_info->sha1 == d->sha1);


	dmesh_remove(d->sha1, download_addr(d), download_port(d),
		d->record_index, d->file_name);

	if (GNET_PROPERTY(download_debug) > 1) {
		g_debug("download at %s \"%u/%s\" becomes "
			"\"/uri-res/N2R?urn:sha1:%s\"",
			host_addr_port_to_string(download_addr(d), download_port(d)),
			d->record_index, d->file_name, sha1_base32(d->sha1));
    }

	d->record_index = URN_INDEX;


	xd = has_same_download(d->file_name, d->sha1, d->file_size,
			download_guid(d), download_addr(d), download_port(d));

	if (xd != NULL && xd != d) {
		download_check(xd);
		download_stop(d, GTA_DL_ERROR, _("Download was a duplicate"));
		return FALSE;
	}

	return TRUE;
}
