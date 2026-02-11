sdb_query_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	SymbolDBQueryPriv *priv;

	g_return_if_fail (SYMBOL_DB_IS_QUERY (object));
	priv = SYMBOL_DB_QUERY (object)->priv;

	switch (prop_id)
	{
	case PROP_QUERY_NAME:
		g_value_set_enum (value, priv->name);
		break;
	case PROP_QUERY_MODE:
		g_value_set_enum (value, priv->mode);
		break;
	case PROP_FILTERS:
		g_value_set_int (value, priv->filters);
		break;
	case PROP_FILE_SCOPE:
		g_value_set_enum (value, priv->file_scope);
		break;
	case PROP_STATEMENT:
		g_value_set_object (value, priv->stmt);
		break;
	case PROP_LIMIT:
		g_value_copy (gda_holder_get_value (priv->param_limit), value);
		break;
	case PROP_OFFSET:
		g_value_copy (gda_holder_get_value (priv->param_offset), value);
		break;
	case PROP_GROUP_BY:
		g_value_set_enum (value, priv->group_by);
		break;
	case PROP_ORDER_BY:
		g_value_set_enum (value, priv->order_by);
		break;
	case PROP_DB_ENGINE_SYSTEM:
		g_value_set_object (value, priv->dbe_system);
		break;
	case PROP_DB_ENGINE_PROJECT:
		g_value_set_object (value, priv->dbe_project);
		break;
	case PROP_DB_ENGINE_SELECTED:
		g_value_set_object (value, priv->dbe_selected);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
