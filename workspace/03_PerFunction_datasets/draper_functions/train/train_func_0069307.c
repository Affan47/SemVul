draw_panel_label(GkrellmPanel *p, gboolean to_bg)
	{
	GkrellmLabel		*lbl	= p->label;
	GkrellmTextstyle	*ts		= p->textstyle;
	GkrellmMargin		*m;
	gchar				*s;
	gint				xdst;

	if (   lbl && ts
		&& ((s = lbl->string) != NULL)
		&& lbl->position >= 0
	   )
		{
		m = gkrellm_get_style_margins(p->style);
		lbl->width = gkrellm_gdk_string_width(ts->font, s) + ts->effect;
		xdst = gkrellm_label_x_position(lbl->position, p->w,
					lbl->width, m->left);
		lbl->x_panel = xdst;
		gkrellm_draw_string(p->pixmap, ts, xdst, lbl->y_panel, s);
		if (to_bg)
			gkrellm_draw_string(p->bg_pixmap, ts, xdst, lbl->y_panel, s);
		}
	}
