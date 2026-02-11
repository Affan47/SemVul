upload_special_flushed(void *arg)
{
	struct upload *u = cast_to_upload(arg);

	g_assert(u->special);
	g_assert(u->special->close);


	(*u->special->close)(u->special, TRUE);
	u->special = NULL;

	if (GNET_PROPERTY(upload_debug))
		g_debug("%s from %s (%s) done: %s bytes, %s sent",
			u->name,
			host_addr_to_string(u->socket->addr),
			upload_vendor_str(u),
			uint64_to_string(u->sent),
			uint64_to_string2(u->file_size));

	upload_fire_upload_info_changed(u);
	upload_completed(u);
}
