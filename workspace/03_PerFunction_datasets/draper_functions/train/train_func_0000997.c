stash_group_free(StashGroup *group)
{
	StashPref *entry;
	guint i;

	foreach_ptr_array(entry, i, group->entries)
	{
		if (entry->widget_type == GTK_TYPE_RADIO_BUTTON)
		{
			g_free(entry->extra.radio_buttons);
		}
		g_slice_free(StashPref, entry);
	}
	g_ptr_array_free(group->entries, TRUE);
	g_free(group);
}
