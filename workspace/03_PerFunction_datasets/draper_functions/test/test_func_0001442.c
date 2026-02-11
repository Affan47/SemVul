copy_data_free (gpointer user_data)
{
	CopyData *data = user_data;

	g_object_unref (data->mechanism);
	g_strfreev (data->includes);
	g_strfreev (data->excludes);
	g_strfreev (data->actions);
	if (data->value)
		gconf_value_free (data->value);
	if (data->destroy)
		data->destroy (data->user_data);
	g_free (data);
}
