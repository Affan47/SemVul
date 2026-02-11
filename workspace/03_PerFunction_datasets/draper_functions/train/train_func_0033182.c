nemo_entry_finalize (GObject *object)
{
	NemoEntry *entry;

	entry = NEMO_ENTRY (object);

	if (entry->details->select_idle_id != 0) {
		g_source_remove (entry->details->select_idle_id);
	}

	g_free (entry->details);

	G_OBJECT_CLASS (nemo_entry_parent_class)->finalize (object);
}
