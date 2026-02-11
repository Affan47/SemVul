go_data_cache_field_is_base (GODataCacheField const *field)
{
	g_return_val_if_fail (IS_GO_DATA_CACHE_FIELD (field), FALSE);
	g_print ("[%d] %s : parent = %d\n", field->indx, field->name->str,
		 field->group_parent);
	return field->group_parent < 0 || field->group_parent == field->indx;
}
