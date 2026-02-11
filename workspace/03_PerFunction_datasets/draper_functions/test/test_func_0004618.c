gkrellm_log_register(
	GkrellmLogFunc log,
	GkrellmLogInitFunc init,
	GkrellmLogCleanupFunc cleanup)
	{
	GkrellmLogFacility *f;
	gint i;

	if (!s_log_facility_ptr_array)
		return FALSE;


	for (i = 0; i < s_log_facility_ptr_array->len; i++)
		{
		f = (g_ptr_array_index(s_log_facility_ptr_array, i));
		if (f->log == log)
			return TRUE;
		}

	if (init != NULL && init() == FALSE)
		return FALSE;


	f = g_new0(GkrellmLogFacility, 1);
	f->log = log;
	f->cleanup = cleanup;


	g_ptr_array_add(s_log_facility_ptr_array, (gpointer)f);
	return TRUE;
	}
