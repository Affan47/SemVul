on_update_img_preview( GtkFileChooser *chooser, GtkImage* img )
{
    char* file = gtk_file_chooser_get_preview_filename(chooser);
    GdkPixbuf* pix = NULL;
    if(file)
    {
        pix = gdk_pixbuf_new_from_file_at_scale( file, 128, 128, TRUE, NULL );
        g_free( file );
    }
    if(pix)
    {
        gtk_file_chooser_set_preview_widget_active(chooser, TRUE);
        gtk_image_set_from_pixbuf(img, pix);
        g_object_unref(pix);
    }
    else
    {
        gtk_image_clear(img);
        gtk_file_chooser_set_preview_widget_active(chooser, FALSE);
    }
}
