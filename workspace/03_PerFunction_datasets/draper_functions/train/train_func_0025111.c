addr_slist_compare (GSList *a, GSList *b)
{
	GSList *iter_a, *iter_b;
	gboolean found = FALSE;

	for (iter_a = a; iter_a; iter_a = g_slist_next (iter_a)) {
		NMIP6Address *addr_a = (NMIP6Address *) iter_a->data;

		for (iter_b = b, found = FALSE; iter_b; iter_b = g_slist_next (iter_b)) {
			NMIP6Address *addr_b = (NMIP6Address *) iter_b->data;

			if (nm_ip6_address_compare (addr_a, addr_b)) {
				found = TRUE;
				break;
			}
		}

		if (!found)
			return FALSE;
	}
	return TRUE;
}
