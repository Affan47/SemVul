g_mime_object_new_type (const char *type, const char *subtype)
{
	struct _type_bucket *bucket;
	struct _subtype_bucket *sub;
	GType obj_type;

	g_return_val_if_fail (type != NULL, NULL);

	if ((bucket = g_hash_table_lookup (type_hash, type))) {
		if (!(sub = g_hash_table_lookup (bucket->subtype_hash, subtype)))
			sub = g_hash_table_lookup (bucket->subtype_hash, "*");

		obj_type = sub ? sub->object_type : 0;
	} else {
		bucket = g_hash_table_lookup (type_hash, "*");
		obj_type = bucket ? bucket->object_type : 0;
	}

	if (!obj_type) {

		if ((bucket = g_hash_table_lookup (type_hash, "*"))) {
			sub = g_hash_table_lookup (bucket->subtype_hash, "*");
			obj_type = sub ? sub->object_type : 0;
		}

		if (!obj_type)
			return NULL;
	}

	return g_object_newv (obj_type, 0, NULL);
}
