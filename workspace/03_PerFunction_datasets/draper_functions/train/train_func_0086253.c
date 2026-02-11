gdk_pixbuf__ani_image_begin_load (GdkPixbufModuleSizeFunc size_func,
                                  GdkPixbufModulePreparedFunc prepared_func,
				  GdkPixbufModuleUpdatedFunc  updated_func,
				  gpointer user_data,
				  GError **error)
{
        AniLoaderContext *context;

        context = g_new0 (AniLoaderContext, 1);

        context->prepared_func = prepared_func;
        context->updated_func = updated_func;
        context->user_data = user_data;

        context->pos = 0;

        context->buffer_size = 4096;
        context->buffer = g_try_malloc (context->buffer_size);
        if (!context->buffer)
	{
		context_free (context);
		g_set_error_literal (error,
                                     GDK_PIXBUF_ERROR,
                                     GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
                                     _("Not enough memory to load animation"));
		return NULL;
	}

        context->byte = context->buffer;
        context->n_bytes = 0;

        return (gpointer) context;
}
