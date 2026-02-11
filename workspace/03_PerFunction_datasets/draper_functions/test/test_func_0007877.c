gsb_select_icon_set_logo_pixbuf ( GdkPixbuf *pixbuf )
{
    if ( pixbuf_logo != NULL )
        g_object_unref ( G_OBJECT ( pixbuf_logo ) );

    if ( gdk_pixbuf_get_width (pixbuf) > LOGO_WIDTH ||
	     gdk_pixbuf_get_height (pixbuf) > LOGO_HEIGHT )
	{
        pixbuf_logo = gsb_select_icon_resize_logo_pixbuf ( pixbuf );
	}
    else
        pixbuf_logo = pixbuf ;
}
