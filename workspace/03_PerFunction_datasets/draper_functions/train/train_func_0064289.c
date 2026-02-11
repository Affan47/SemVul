image_loader_area_updated_cb(gpointer loader,
				 guint x, guint y, guint w, guint h,
				 gpointer data)
{
	ImageLoader *il = data;

	if (!image_loader_get_pixbuf(il))
		{
		image_loader_sync_pixbuf(il);
		if (!image_loader_get_pixbuf(il))
			{
			log_printf("critical: area_ready signal with NULL pixbuf (out of mem?)\n");
			}
		}

	g_mutex_lock(il->data_mutex);
	if (il->delay_area_ready)
		image_loader_queue_delayed_area_ready(il, x, y, w, h);
	else
		image_loader_emit_area_ready(il, x, y, w, h);

	if (il->stopping) il->backend.abort(il->loader);

	g_mutex_unlock(il->data_mutex);
}
