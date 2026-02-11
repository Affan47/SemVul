camel_imapx_command_new (CamelIMAPXServer *is,
                         const gchar *name,
                         CamelFolder *select,
                         const gchar *format,
                         ...)
{
	CamelIMAPXRealCommand *real_ic;
	static gint tag = 0;
	va_list ap;

	real_ic = g_slice_new0 (CamelIMAPXRealCommand);


	real_ic->ref_count = 1;
	real_ic->buffer = g_string_sized_new (512);
	g_cond_init (&real_ic->done_sync_cond);
	g_mutex_init (&real_ic->done_sync_mutex);


	real_ic->public.is = is;
	real_ic->public.tag = tag++;
	real_ic->public.name = name;
	real_ic->public.select = select;
	g_queue_init (&real_ic->public.parts);

	if (format != NULL && *format != '\0') {
		va_start (ap, format);
		camel_imapx_command_addv (
			(CamelIMAPXCommand *) real_ic, format, ap);
		va_end (ap);
	}

	return (CamelIMAPXCommand *) real_ic;
}
