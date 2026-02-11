_midgard_schema_finalize (GObject *object)
{
	g_assert (object != NULL);
	MidgardSchema *self = (MidgardSchema *) object;

	g_hash_table_foreach (self->types, _get_schema_trash, NULL);
	g_hash_table_destroy (self->types);

	GSList *l = NULL;
	for (l = schema_trash; l != NULL; l = l->next){
		midgard_core_schema_type_attr_free ((MgdSchemaTypeAttr *) l->data);
	}

	if (schema_trash) {
		g_slist_free (schema_trash);
		schema_trash = NULL;
	}
}
