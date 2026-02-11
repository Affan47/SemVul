midgard_core_dbobject_class_list_properties (MidgardDBObjectClass *klass, guint *n_props)
{
	g_return_val_if_fail (klass != NULL, NULL);

	MgdSchemaTypeAttr *type_attr = klass->dbpriv->storage_data;
	if (type_attr->params) {
		*n_props = g_slist_length (type_attr->_properties_list);
		return type_attr->params;
	}

	GSList *l;
	guint i = 0;
	guint n_params = g_slist_length (type_attr->_properties_list);
	type_attr->params = g_new (GParamSpec *, n_params);

	for (l = type_attr->_properties_list; l != NULL; l = l->next, i++) {
		type_attr->params[i] = g_object_class_find_property (G_OBJECT_CLASS (klass), (const gchar *) l->data);
	}

	*n_props = n_params;
	return type_attr->params;
}
