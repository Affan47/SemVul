gkrellm_decal_text_nth_inserted_get_offset(GkrellmDecal *d, gint n,
			gint *x, gint *y)
	{
	GList		*list;
	GkrellmText	*tx;

	if (!d || (list = g_list_nth(d->text_list, n)) == NULL)
		return;

	tx = (GkrellmText *) list->data;
	if (x)
		*x = tx->x_off;
	if (y)
		*y = tx->y_off + d->y_ink;
	}
