memory_configure(void)
{
	gint groups_per_line;

	back_bytes_per_line = pref_memory_bytes_per_line;
	bytes_per_line = pref_memory_bytes_per_line;
	if ((unsigned) (bytes_per_line - 8) > MAX_BYTES_PER_LINE - 8)
		bytes_per_line = 16;

	groups_per_line = bytes_per_line / bytes_per_group;
	bytes_per_line = groups_per_line * bytes_per_group;
}
