almanah_entry_set_last_edited (AlmanahEntry *self, GDate *last_edited)
{
	g_return_if_fail (ALMANAH_IS_ENTRY (self));
	g_return_if_fail (last_edited != NULL && g_date_valid (last_edited) == TRUE);

	self->priv->last_edited = *last_edited;
}
