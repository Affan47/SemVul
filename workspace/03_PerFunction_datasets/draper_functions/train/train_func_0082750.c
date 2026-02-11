mono_gc_wbarrier_generic_store_atomic (gpointer ptr, GCObject *value)
{
	HEAVY_STAT (++stat_wbarrier_generic_store_atomic);

	SGEN_LOG (8, "Wbarrier atomic store at %p to %p (%s)", ptr, value, value ? sgen_client_vtable_get_name (SGEN_LOAD_VTABLE (value)) : "null");

	InterlockedWritePointer ((volatile gpointer *)ptr, value);

	if (ptr_in_nursery (value) || concurrent_collection_in_progress)
		mono_gc_wbarrier_generic_nostore (ptr);

	sgen_dummy_use (value);
}
