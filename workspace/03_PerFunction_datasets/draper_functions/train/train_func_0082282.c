gdk_pixbuf__pcx_begin_load(GdkPixbufModuleSizeFunc size_func,
                           GdkPixbufModulePreparedFunc prepared_func,
                           GdkPixbufModuleUpdatedFunc updated_func,
                           gpointer user_data, GError **error)
{
	struct pcx_context *context;

	context = g_new0(struct pcx_context, 1);
	if(!context)
		return NULL;

	context->header = g_try_malloc(sizeof(struct pcx_header));
	if(!context->header) {
		g_free(context);
		g_set_error_literal(error, GDK_PIXBUF_ERROR, GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY, _("Couldn't allocate memory for header"));
		return NULL;
	}

	context->size_func = size_func;
	context->updated_func = updated_func;
	context->prepared_func = prepared_func;
	context->user_data = user_data;

	context->current_task = PCX_TASK_LOAD_HEADER;

	context->buf = g_try_malloc(sizeof(guchar) * 512);
	if(!context->buf) {
		g_free(context->header);
		g_free(context);
		g_set_error_literal(error, GDK_PIXBUF_ERROR, GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY, _("Couldn't allocate memory for context buffer"));
		return NULL;
	}
	context->buf_size = 512;

	context->header_loaded = FALSE;

	return context;
}
