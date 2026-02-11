check_auth_data_free (CheckAuthData *data)
{
	g_object_unref (data->mechanism);
	g_strfreev (data->actions);
	if (data->destroy)
		data->destroy (data->user_data);
        g_object_unref (data->subject);
	g_free (data);
}
