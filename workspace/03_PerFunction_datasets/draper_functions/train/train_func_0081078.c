odf_get_gog_style_name_from_obj (GogObject const *obj)
{
	GObjectClass *klass = G_OBJECT_GET_CLASS (G_OBJECT (obj));

	if (NULL != g_object_class_find_property (klass, "style")) {
		GOStyle *style = NULL;
		gchar *name;
		g_object_get (G_OBJECT (obj), "style", &style, NULL);
		name = odf_get_gog_style_name (style, obj);
		g_object_unref (style);
		return name;
	} else
		return odf_get_gog_style_name (NULL, obj);
	return NULL;
}
