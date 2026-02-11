gdata_gd_name_new (const gchar *given_name, const gchar *family_name)
{
	g_return_val_if_fail (given_name == NULL || *given_name != '\0', NULL);
	g_return_val_if_fail (family_name == NULL || *family_name != '\0', NULL);
	return g_object_new (GDATA_TYPE_GD_NAME, "given-name", given_name, "family-name", family_name, NULL);
}
