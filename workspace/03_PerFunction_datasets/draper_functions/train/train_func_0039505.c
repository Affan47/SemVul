dma_variable_data_new(const gchar *const name, gboolean auto_update)
{
	DmaVariableData *data;

	data = g_new0 (DmaVariableData, 1);
	if (name != NULL)
	{
		data->name = g_strdup (name);
	}

	data->auto_update = auto_update;

	return data;
}
