ebews_populate_notes (EBookBackendEws *ebews,
		      EContact *contact,
		      EEwsItem *item,
		      GCancellable *cancellable,
		      GError **error)
{
	const gchar *notes = e_ews_item_get_notes (item);
	if (!notes)
		return;

	e_contact_set (contact, E_CONTACT_NOTE, notes);
}
