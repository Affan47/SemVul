name_or_uri_field_activate (NemoEntry *entry)
{
	g_assert (NEMO_IS_ENTRY (entry));

	update_bookmark_from_text ();
	nemo_entry_select_all_at_idle (entry);
}
