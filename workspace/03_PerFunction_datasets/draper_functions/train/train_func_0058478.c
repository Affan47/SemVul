sgen_pin_queue_clear_discarded_entries (GCMemSection *section, size_t max_pin_slot)
{
	void **start = sgen_pinning_get_entry (section->pin_queue_last_entry);
	void **end = sgen_pinning_get_entry (max_pin_slot);
	void *addr;

	for (; start < end; ++start) {
		addr = *start;
		if ((char*)addr < section->data || (char*)addr > section->end_data)
			break;
		*start = NULL;
	}
}
