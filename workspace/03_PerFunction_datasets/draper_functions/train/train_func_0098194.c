gee_multi_set_base_init (GeeMultiSetIface * iface) {
	static gboolean initialized = FALSE;
	if (!initialized) {
		initialized = TRUE;
		iface->get_read_only_view = gee_multi_set_real_get_read_only_view;
	}
}
