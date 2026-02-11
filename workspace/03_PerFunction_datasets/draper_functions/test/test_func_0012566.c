_e2_task_backend_parse_mode (gchar *mode, E2_ChmodData *data)
{
	data->setmask = 0;
	data->clearmask = 0;
	if (strchr (mode, ',') != NULL)
	{
		gchar **tmp1, **tmp2;
		tmp1 = tmp2 = g_strsplit (mode, ",", -1);
		while (*tmp1 != NULL)
		{
			_e2_task_backend_parse_flags (*tmp1, &(data->setmask), &(data->clearmask));
			tmp1++;
		}
		g_strfreev (tmp2);
	}
	else
		if ((strchr (mode, '+') != NULL) || (strchr (mode, '-') != NULL))

			_e2_task_backend_parse_flags (mode, &(data->setmask), &(data->clearmask));
	else
	{
		glong tmp = strtol (mode, NULL, 8);
		data->setmask = (mode_t) tmp;
		data->clearmask = ALLPERMS;
	}
	data->clearmask = ~data->clearmask;
}
