getlinelength_i(ht_ltextfile_line *e) const
{
	if (e) {
		if (e->is_in_memory) {
			return e->in_memory.len;
		} else {
			return e->on_disk.len;
		}
	}
	return 0;
}
