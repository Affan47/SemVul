gm_searchable_get_text_view(GmSearchable *self) {
	GmSearchableInterface *iface;

	g_return_val_if_fail(GM_IS_SEARCHABLE(self), FALSE);

	iface = GM_SEARCHABLE_GET_INTERFACE(self);

	return gm_searchable_interface_get_text_view(self, iface);
}
