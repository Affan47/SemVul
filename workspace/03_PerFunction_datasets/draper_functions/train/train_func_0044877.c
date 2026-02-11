rs_timeout_cb(gpointer user_data)
{
	struct rs_cb_data *data = user_data;

	DBG("user data %p", user_data);

	if (data == NULL)
		return FALSE;

	if (data->callback != NULL)
		data->callback(NULL, 0, data->user_data);

	data->rs_timeout = 0;
	rs_cleanup(data);
	return FALSE;
}
