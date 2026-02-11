addr_array_compare (GArray *a, GArray *b)
{
	int i, j;
	gboolean found = FALSE;

	for (i = 0; i < a->len; i++) {
		for (j = 0, found = FALSE; j < b->len; j++) {
			if (g_array_index (a, guint32, i) == g_array_index (b, guint32, j)) {
				found = TRUE;
				break;
			}
		}

		if (!found)
			return FALSE;
	}
	return TRUE;
}
