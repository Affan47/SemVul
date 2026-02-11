gog_styled_object_set_style (GOStyledObject *gso,
			     GOStyle *style)
{
	gboolean resize;
	GogStyledObject *ggso;

	g_return_val_if_fail (GO_IS_STYLED_OBJECT (gso), FALSE);
	ggso = GOG_STYLED_OBJECT (gso);
	if (ggso->style == style)
		return FALSE;
	style = go_style_dup (style);


	go_styled_object_apply_theme (gso, style);
	resize = go_style_is_different_size (ggso->style, style);
	if (ggso->style != NULL)
		g_object_unref (ggso->style);
	ggso->style = style;
	go_styled_object_style_changed (gso);

	return resize;
}
