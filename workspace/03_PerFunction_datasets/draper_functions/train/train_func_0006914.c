find_hints_item (GPtrArray *hints, const char *item)
{
	int i;

	for (i = 0; i < hints->len; i++) {
		if (!strcmp (item, (const char *) g_ptr_array_index (hints, i)))
			return TRUE;
	}
	return FALSE;
}
