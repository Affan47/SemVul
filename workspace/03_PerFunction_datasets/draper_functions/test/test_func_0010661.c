gkrellm_decal_scroll_text_get_size(GkrellmDecal *d, gint *w, gint *h)
	{
	if (!d)
		return;
	if (w)
		*w = d->scroll_width;
	if (h)
		*h = d->scroll_height
					+ ((d->flags & DF_SCROLL_TEXT_V_LOOP) ? d->y_ink : 0);
	}
