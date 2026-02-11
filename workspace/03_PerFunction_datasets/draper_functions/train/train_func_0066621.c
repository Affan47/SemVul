finalize (GObject *object)
{
	NautilusLocationEntry *entry;

	entry = NAUTILUS_LOCATION_ENTRY (object);

	g_object_unref (entry->details->completer);
	g_free (entry->details->special_text);

	g_clear_object (&entry->details->last_location);

	G_OBJECT_CLASS (nautilus_location_entry_parent_class)->finalize (object);
}
