_collector_find_class_property(
		MidgardCollector *self, const gchar *propname)
{
	const gchar *table_field =
		midgard_core_class_get_property_tablefield(
				MIDGARD_DBOBJECT_CLASS(self->priv->klass),
				propname);


	if(table_field == NULL) {

		MidgardMetadataClass *mklass =
			(MidgardMetadataClass*) g_type_class_peek(g_type_from_name("MidgardMetadata"));
		GParamSpec *pspec = g_object_class_find_property (G_OBJECT_CLASS (mklass), propname);

		if (pspec)
			return "";
	}

	return table_field;
}
