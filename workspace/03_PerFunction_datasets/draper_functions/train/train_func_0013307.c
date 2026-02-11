gdata_media_category_new (const gchar *category, const gchar *scheme, const gchar *label)
{
	g_return_val_if_fail (category != NULL && *category != '\0', NULL);
	g_return_val_if_fail (scheme == NULL || *scheme != '\0', NULL);
	return g_object_new (GDATA_TYPE_MEDIA_CATEGORY, "category", category, "scheme", scheme, "label", label, NULL);
}
