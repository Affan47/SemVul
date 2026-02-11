update_array_data_free (UpdateArrayData *update_data)
{
	if (!update_data)
		return;

	if (update_data->sparql_array) {


		g_array_free (update_data->sparql_array, TRUE);
	}

	if (update_data->bulk_ops) {


		g_ptr_array_free (update_data->bulk_ops, TRUE);
	}

	g_ptr_array_foreach (update_data->tasks,
	                     (GFunc) remove_task_foreach,
	                     update_data->buffer);
	g_ptr_array_free (update_data->tasks, TRUE);

	g_array_free (update_data->error_map, TRUE);
	g_slice_free (UpdateArrayData, update_data);
}
