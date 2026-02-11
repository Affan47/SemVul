_midgard_query_select_list_objects (MidgardQuerySelect *self, guint *n_objects)
{
	g_return_val_if_fail (self != NULL, NULL);

	*n_objects = 0;
	GdaDataModel *model = GDA_DATA_MODEL (MIDGARD_QUERY_EXECUTOR (self)->priv->resultset);
	if (!model || (model && !GDA_IS_DATA_MODEL (model)))
		return NULL;

	guint i;
	guint rows = gda_data_model_get_n_rows (model);
	if (rows < 1)
		return NULL;

	MidgardConnection *mgd = MIDGARD_QUERY_EXECUTOR (self)->priv->mgd;
	MidgardDBObjectClass *klass = MIDGARD_QUERY_EXECUTOR (self)->priv->storage->priv->klass;
	MidgardDBObject **objects = g_new (MidgardDBObject *, rows+1);

	for (i = 0; i < rows; i++) {
		GParamSpec *guid_spec = NULL;
		objects[i] = g_object_new (G_OBJECT_CLASS_TYPE (klass), "connection", mgd, NULL);
		MGD_OBJECT_IN_STORAGE (objects[i]) = TRUE;
		MIDGARD_DBOBJECT(objects[i])->dbpriv->datamodel = g_object_ref (model);
		MIDGARD_DBOBJECT(objects[i])->dbpriv->row = i;

		if (MIDGARD_QUERY_EXECUTOR (self)->priv->read_only) {
			guid_spec = g_object_class_find_property (G_OBJECT_CLASS (klass), "guid");
			if (guid_spec) {
				gint col_idx = gda_data_model_get_column_index (model, "guid");
				if (col_idx == -1) {
					g_warning ("Missed column for registered 'guid' column. (%s)", G_OBJECT_CLASS_NAME (klass));
					continue;
				}
				const GValue *gval = gda_data_model_get_value_at (model, col_idx, i, NULL);

				MGD_OBJECT_GUID (objects[i]) = g_value_dup_string (gval);
			}
		} else {
			MIDGARD_DBOBJECT_GET_CLASS (objects[i])->dbpriv->set_from_data_model (
					MIDGARD_DBOBJECT (objects[i]), model, i, 0);
		}
	}

	objects[i] = NULL;
	*n_objects = rows;

	return objects;
}
