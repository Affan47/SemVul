gm_searchable_interface_get_text_view(GmSearchable *self,
		GmSearchableInterface *iface) {
	g_return_val_if_fail(iface != NULL, FALSE);

	if (iface->get_text_view == NULL) {
		return NULL;
	}

	return (* iface->get_text_view) (self);
}
