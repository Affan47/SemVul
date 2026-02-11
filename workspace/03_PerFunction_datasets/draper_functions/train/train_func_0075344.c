pan_window_dispose_tile_cb(PixbufRenderer *pr, gint x, gint y,
				       gint width, gint height, GdkPixbuf *pixbuf, gpointer data)
{
	PanWindow *pw = data;
	GList *list;
	GList *work;

	list = pan_layout_intersect(pw, x, y, width, height);
	work = list;
	while (work)
		{
		PanItem *pi;

		pi = work->data;
		work = work->next;

		if (pi->refcount > 0)
			{
			pi->refcount--;

			if (pi->refcount == 0)
				{
				if (pi->queued)
					{
					pw->queue = g_list_remove(pw->queue, pi);
					pi->queued = FALSE;
					}
				if (pw->queue_pi == pi) pw->queue_pi = NULL;
				if (pi->pixbuf)
					{
					g_object_unref(pi->pixbuf);
					pi->pixbuf = NULL;
					}
				}
			}
		}

	g_list_free(list);
}
