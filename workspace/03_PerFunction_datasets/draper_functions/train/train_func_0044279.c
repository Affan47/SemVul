mask_special_array (const char *type, gboolean *special_array, gboolean *any_special)
{
	OurGtkType *gtype;

	init_type_hash();

	gtype = g_hash_table_lookup(type_hash, type);

	if(gtype && gtype->special >= 0) {
		special_array[gtype->special] = TRUE;
		*any_special = TRUE;
	}
}
