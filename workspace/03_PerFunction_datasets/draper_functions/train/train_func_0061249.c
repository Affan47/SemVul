ldapctl_compare_list(GList *l1, GList *l2) {
	gchar *first, *second;
	if (! l1 && ! l2)
		return TRUE;
	if ((! l1 && l2) || (l1 && ! l2))
		return FALSE;
	while (l1 && l2) {
		first = (gchar *) l1->data;
		second = (gchar *) l2->data;

		if ( ! (first && second) || strcmp(first, second) != 0) {
			return FALSE;
		}
		l1 = g_list_next(l1);
		l2 = g_list_next(l2);
	}
	return TRUE;
}
