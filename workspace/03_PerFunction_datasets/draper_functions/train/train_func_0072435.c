execute_data_free (ExecuteData *exec_data)
{
	if (exec_data == NULL)
		return;

	if (exec_data->cancel_id != 0)
		g_cancellable_disconnect (exec_data->cancellable, exec_data->cancel_id);

	_g_object_unref (exec_data->process);
	_g_object_unref (exec_data->cancellable);
	_g_object_unref (exec_data->result);
	fr_error_free (exec_data->error);
	fr_error_free (exec_data->first_error);
	_g_string_list_free (exec_data->first_error_stdout);
	_g_string_list_free (exec_data->first_error_stderr);
	g_free (exec_data);
}
