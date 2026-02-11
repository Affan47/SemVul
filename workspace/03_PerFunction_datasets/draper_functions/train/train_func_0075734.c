eog_print_preview_set_image_position (EogPrintPreview *preview,
				      gdouble x,
				      gdouble y)
{
	EogPrintPreviewPrivate *priv;
	gfloat x_align, y_align;
	gdouble width, height;

	g_return_if_fail (EOG_IS_PRINT_PREVIEW (preview));

	priv = preview->priv;

	if (x != -1) {
		width  = gdk_pixbuf_get_width (priv->image) * priv->i_scale / 72.;
		x_align = CLAMP (x/(priv->p_width - priv->l_margin - priv->r_margin - width), 0, 1);
		g_object_set (preview, "image-x-align", x_align, NULL);
	}

	if (y != -1) {
		height  = gdk_pixbuf_get_height (priv->image) * priv->i_scale / 72.;
		y_align = CLAMP (y/(priv->p_height - priv->t_margin - priv->b_margin - height), 0, 1);
		g_object_set (preview, "image-y-align", y_align, NULL);
	}
}
