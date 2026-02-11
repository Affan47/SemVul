sdb_engine_add_new_tmp_heritage_scope (SymbolDBEngine * dbe,
									   const tagEntry * tag_entry,
									   gint symbol_referer_id)
{
	SymbolDBEnginePriv *priv;
	const gchar *field_inherits, *field_struct, *field_typeref,
		*field_enum, *field_union, *field_class, *field_namespace;
	TableMapTmpHeritage * node;

	priv = dbe->priv;

	node = g_slice_new0 (TableMapTmpHeritage);
	node->symbol_referer_id = symbol_referer_id;

	if ((field_inherits = tagsField (tag_entry, "inherits")) != NULL)
	{
		node->field_inherits = g_strdup (field_inherits);
	}

	if ((field_struct = tagsField (tag_entry, "struct")) != NULL)
	{
		node->field_struct = g_strdup (field_struct);
	}

	if ((field_typeref = tagsField (tag_entry, "typeref")) != NULL)
	{
		node->field_typeref = g_strdup (field_typeref);
	}

	if ((field_enum = tagsField (tag_entry, "enum")) != NULL)
	{
		node->field_enum = g_strdup (field_enum);
	}

	if ((field_union = tagsField (tag_entry, "union")) != NULL)
	{
		node->field_union = g_strdup (field_union);
	}

	if ((field_class = tagsField (tag_entry, "class")) != NULL)
	{
		node->field_class = g_strdup (field_class);
	}

	if ((field_namespace = tagsField (tag_entry, "namespace")) != NULL)
	{
		node->field_namespace = g_strdup (field_namespace);
	}

	g_queue_push_head (priv->tmp_heritage_tablemap, node);
}
