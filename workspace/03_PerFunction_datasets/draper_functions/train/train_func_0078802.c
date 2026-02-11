add_attributetype(GHashTable *types, LDAPAttributeType *at)
{
	int i;
	char **names = at->at_names;

	g_hash_table_insert(types, at->at_oid, at);
	if (names)
		for (i = 0; names[i]; i++)
			g_hash_table_insert(types, names[i], at);
}
