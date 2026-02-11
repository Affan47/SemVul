geoclue_manual_set_address_common (GeoclueManual *manual,
                                   int valid_for,
                                   GHashTable *address)
{
	if (manual->event_id > 0) {
		g_source_remove (manual->event_id);
	}

	manual->timestamp = time (NULL);

	g_hash_table_destroy (manual->address);
	manual->address = address;

	geoclue_accuracy_set_details (manual->accuracy,
	                              get_accuracy_for_address (address),
	                              0, 0);

	gc_iface_address_emit_address_changed (GC_IFACE_ADDRESS (manual),
	                                       manual->timestamp,
	                                       manual->address,
	                                       manual->accuracy);

	if (valid_for > 0) {
		manual->event_id = g_timeout_add (valid_for * 1000,
		                                  (GSourceFunc)validity_ended,
		                                  manual);
	}
}
