tracker_sparql_buffer_update_cb (GObject      *object,
                                 GAsyncResult *result,
                                 gpointer      user_data)
{
	UpdateData *update_data = user_data;
	SparqlTaskData *task_data;
	GError *error = NULL;

	tracker_sparql_connection_update_finish (TRACKER_SPARQL_CONNECTION (object),
	                                         result, &error);

	task_data = tracker_task_get_data (update_data->task);


	g_simple_async_result_set_op_res_gpointer (task_data->result,
						   update_data->task,
						   NULL);
	if (error) {
		g_simple_async_result_set_from_error (task_data->result, error);
		g_error_free (error);
	}

	g_simple_async_result_complete (task_data->result);

	tracker_task_pool_remove (TRACKER_TASK_POOL (update_data->buffer),
	                          update_data->task);
	g_slice_free (UpdateData, update_data);
}
