contacts_list_pane_filter_entry_changed_timeout (ContactsListPane* self) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	self->priv->filter_entry_changed_id = (guint) 0;
	contacts_list_pane_refilter (self);
	result = FALSE;
	return result;
}
