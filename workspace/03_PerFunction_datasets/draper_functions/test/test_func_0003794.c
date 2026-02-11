free_hash_entry(const void *key, void *value, void *unused_data)
{
	struct term_counts *val = value;
	char *s = deconstify_pointer(key);

	(void) unused_data;

	wfree(s, 1 + strlen(s));
	WFREE(val);
	return TRUE;
}
