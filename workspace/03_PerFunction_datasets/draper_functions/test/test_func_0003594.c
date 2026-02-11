gdk_pixbuf__tga_begin_load(GdkPixbufModuleSizeFunc f0,
                                           GdkPixbufModulePreparedFunc f1,
					   GdkPixbufModuleUpdatedFunc f2,
					   gpointer udata, GError **err)
{
	TGAContext *ctx;

	ctx = g_try_malloc(sizeof(TGAContext));
	if (!ctx) {
		g_set_error_literal(err, GDK_PIXBUF_ERROR,
                                    GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
                                    _("Cannot allocate memory for TGA context struct"));
		return NULL;
	}

	ctx->hdr = NULL;
	ctx->rowstride = 0;
	ctx->run_length_encoded = FALSE;

	ctx->cmap = NULL;
	ctx->cmap_size = 0;

	ctx->pbuf = NULL;
	ctx->pbuf_bytes = 0;
	ctx->pbuf_bytes_done = 0;
	ctx->pptr = NULL;

	ctx->in = io_buffer_new(err);
	if (!ctx->in) {
		g_free(ctx);
		return NULL;
	}

	ctx->skipped_info = FALSE;
	ctx->prepared = FALSE;
	ctx->done = FALSE;

	ctx->sfunc = f0;
	ctx->pfunc = f1;
	ctx->ufunc = f2;
	ctx->udata = udata;

	return ctx;
}
