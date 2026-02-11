_attributes_matches_mask (const char *attributes,
			  const char *mask)
{
	gboolean   matches = FALSE;
	char     **attributes_v;
	char     **mask_v;
	int        i;

	attributes_v = g_strsplit (attributes, ",", -1);
	mask_v = g_strsplit (mask, ",", -1);
	for (i = 0; ! matches && (mask_v[i] != NULL); i++) {
		int j;

		for (j = 0; ! matches && (attributes_v[j] != NULL); j++) {
			matches = attribute_matches_mask (attributes_v[j], mask_v[i]);
#if 0
			g_print ("attr: %s <=> mask: %s : %d\n", attributes_v[j], mask_v[i], matches);
#endif
		}
	}

	g_strfreev (mask_v);
	g_strfreev (attributes_v);

	return matches;
}
