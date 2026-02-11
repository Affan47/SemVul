gck_builder_find_ulong (GckBuilder *builder,
                        gulong attr_type,
                        gulong *value)
{
	GckRealBuilder *real = (GckRealBuilder *)builder;

	g_return_val_if_fail (builder != NULL, FALSE);
	g_return_val_if_fail (value != NULL, FALSE);

	if (real->array == NULL)
		return FALSE;

	return find_attribute_ulong ((GckAttribute *)real->array->data,
	                             real->array->len, attr_type, value);
}
