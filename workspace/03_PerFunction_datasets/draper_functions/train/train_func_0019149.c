get_loc (GSettings *settings)
{
	char *path, *schema, *ret;

	g_return_val_if_fail (G_IS_SETTINGS (settings), NULL);

	g_object_get (G_OBJECT (settings),
		      "path", &path,
		      "schema", &schema,
		      NULL);
	ret = g_strdup_printf ("schema: %s (path: %s)", schema, path);
	g_free (schema);
	g_free (path);

	return ret;
}
