gbemol_info_set_image (GbemolInfo* info, GdkPixbuf* img)
{
	GdkPixbuf* scaled;

	if (img)
	{
		scaled = gdk_pixbuf_scale_simple (img, 100, 100, GDK_INTERP_BILINEAR);
		gtk_image_set_from_pixbuf (GTK_IMAGE (info->priv->img_info), scaled);
		g_object_unref (img);
		g_object_unref (scaled);
		gtk_widget_show (info->priv->img_info);
	}
	else
		gtk_widget_hide (info->priv->img_info);
}
