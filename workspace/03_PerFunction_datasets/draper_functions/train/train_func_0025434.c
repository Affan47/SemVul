gsf_infile_zip_set_property (GObject      *object,
			     guint         property_id,
			     GValue const *value,
			     GParamSpec   *pspec)
{
	GsfInfileZip *zip = (GsfInfileZip *)object;

	switch (property_id) {
	case PROP_SOURCE:
		gsf_infile_zip_set_source (zip, g_value_get_object (value));
		break;
	case PROP_INTERNAL_PARENT:
		zip->dup_parent = g_value_get_object (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
