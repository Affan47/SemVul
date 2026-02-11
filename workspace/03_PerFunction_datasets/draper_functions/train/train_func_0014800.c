too_big_gc() {
	if (startGC())
		d_http_cache_table->delete_by_size(d_max_entry_size);
}
