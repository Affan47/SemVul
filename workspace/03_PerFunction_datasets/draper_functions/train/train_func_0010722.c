__certificate_properties_lookup_oid_function (const certificate_properties_oid_function_couple_t *oid_func_table,
									    const gchar *oid)
{
	const certificate_properties_oid_function_couple_t *i;
	if (!oid)
		return 0;
	for (i = oid_func_table; i->oid; i++)
		if (strcmp(i->oid, oid) == 0)
			break;
	return i->function;
}
