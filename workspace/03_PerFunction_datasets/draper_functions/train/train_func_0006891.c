gck_mock_module_set_object (CK_OBJECT_HANDLE object, CK_ATTRIBUTE_PTR attrs,
                            CK_ULONG n_attrs)
{
	GckAttributes *atts;
	GckAttributes *replaced;

	g_return_if_fail (object != 0);
	g_return_if_fail (the_objects);

	atts = g_hash_table_lookup (the_objects, GUINT_TO_POINTER (object));
	g_return_if_fail (atts);

	if (!n_attrs)
		return;

	replaced = replace_attributes (atts, attrs, n_attrs);
	g_hash_table_replace (the_objects, GUINT_TO_POINTER (object), replaced);
}
