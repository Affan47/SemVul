e_name_selector_entry_set_show_address (ENameSelectorEntry *name_selector_entry,
                                        gboolean show)
{
	g_return_if_fail (E_IS_NAME_SELECTOR_ENTRY (name_selector_entry));

	if ((name_selector_entry->priv->show_address ? 1 : 0) == (show ? 1 : 0))
		return;

	name_selector_entry->priv->show_address = show;

	sanitize_entry (name_selector_entry);

	g_object_notify (G_OBJECT (name_selector_entry), "show-address");
}
