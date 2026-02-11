verify_typedef_table_global_constraints (VerifyContext *ctx)
{
	int i;
	guint32 data [MONO_TYPEDEF_SIZE];
	guint32 nested_data [MONO_NESTED_CLASS_SIZE];
	MonoTableInfo *table = &ctx->image->tables [MONO_TABLE_TYPEDEF];
	MonoTableInfo *nested_table = &ctx->image->tables [MONO_TABLE_NESTEDCLASS];
	GHashTable *unique_types = g_hash_table_new_full (&typedef_hash, &typedef_equals, g_free, NULL);

	for (i = 0; i < table->rows; ++i) {
		guint visibility;
		TypeDefUniqueId *type = g_new (TypeDefUniqueId, 1);
		mono_metadata_decode_row (table, i, data, MONO_TYPEDEF_SIZE);

		type->name = mono_metadata_string_heap (ctx->image, data [MONO_TYPEDEF_NAME]);
		type->name_space = mono_metadata_string_heap (ctx->image, data [MONO_TYPEDEF_NAMESPACE]);
		type->resolution_scope = 0;

		visibility = data [MONO_TYPEDEF_FLAGS] & TYPE_ATTRIBUTE_VISIBILITY_MASK;
		if (visibility >= TYPE_ATTRIBUTE_NESTED_PUBLIC && visibility <= TYPE_ATTRIBUTE_NESTED_FAM_OR_ASSEM) {
			int res = search_sorted_table (ctx, MONO_TABLE_NESTEDCLASS, MONO_NESTED_CLASS_NESTED, i + 1);
			g_assert (res >= 0);

			mono_metadata_decode_row (nested_table, res, nested_data, MONO_NESTED_CLASS_SIZE);
			type->resolution_scope = nested_data [MONO_NESTED_CLASS_ENCLOSING];
		}

		if (g_hash_table_lookup (unique_types, type)) {
			ADD_ERROR_NO_RETURN (ctx, g_strdup_printf ("TypeDef table row %d has duplicate for tuple (%s,%s,%x)", i, type->name, type->name_space, type->resolution_scope));
			g_hash_table_destroy (unique_types);
			g_free (type);
			return;
		}
		g_hash_table_insert (unique_types, type, GUINT_TO_POINTER (1));
	}

	g_hash_table_destroy (unique_types);
}
