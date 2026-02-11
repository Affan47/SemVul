build_set_animation (IAnjutaMessageManager* mesg_manager, BuildContext* context)
{
	GtkIconTheme *icon_theme = gtk_icon_theme_get_default ();
	GtkIconInfo *icon_info;
	const gchar *name;
	icon_info = gtk_icon_theme_lookup_icon (icon_theme, "process-working", 16, 0);
	name = gtk_icon_info_get_filename (icon_info);
	if (name != NULL)
	{
		int size = gtk_icon_info_get_base_size (icon_info);
		GdkPixbufSimpleAnim* anim = gdk_pixbuf_simple_anim_new (size, size, 5);
		GdkPixbuf *image = gdk_pixbuf_new_from_file (name, NULL);
		if (image)
		{
			int grid_width = gdk_pixbuf_get_width (image);
			int grid_height = gdk_pixbuf_get_height (image);
			int x,y;
			for (y = 0; y < grid_height; y += size)
			{
				for (x = 0; x < grid_width ; x += size)
				{
					GdkPixbuf *pixbuf = gdk_pixbuf_new_subpixbuf (image, x, y, size,size);
					if (pixbuf)
					{
						gdk_pixbuf_simple_anim_add_frame (anim, pixbuf);
					}
				}
			}
			ianjuta_message_manager_set_view_icon (mesg_manager,
			                                       context->message_view,
			                                       GDK_PIXBUF_ANIMATION (anim), NULL);
			g_object_unref (image);
		}
	}
	gtk_icon_info_free (icon_info);
}
