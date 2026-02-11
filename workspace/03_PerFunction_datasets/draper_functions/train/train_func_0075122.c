image_view_set_pixbuf( ImageView* iv, GdkPixbuf* pixbuf )
{
    if( pixbuf != iv->pix )
    {
        image_view_clear( iv );
        if( G_LIKELY(pixbuf) )
            iv->pix = (GdkPixbuf*)g_object_ref( pixbuf );
        calc_image_area( iv );
        gtk_widget_queue_resize( (GtkWidget*)iv );

    }
}
