gsb_select_icon_change_account_pixbuf ( gint account_number,
                        gchar *filename )
{
    GSList *list_tmp;
    GdkPixbuf *pixbuf;

    if ( icon_buffer
	 &&
	 icon_buffer -> account_number == account_number )
    {
        pixbuf = gdk_pixbuf_new_from_file_at_size ( filename , 32, 32, NULL );
        if ( pixbuf )
        {
            g_object_unref ( icon_buffer -> pixbuf );
            icon_buffer -> pixbuf = pixbuf;

            return icon_buffer -> pixbuf;
        }
        else
            return NULL;
    }

    list_tmp = list_accounts_icon;

    while ( list_tmp )
    {
        struct_account_icon *icon;

        icon = list_tmp -> data;

        if ( icon -> account_number == account_number )
        {
            pixbuf = gdk_pixbuf_new_from_file_at_size ( filename , 32, 32, NULL );
            if ( pixbuf )
            {
                g_object_unref ( icon -> pixbuf );
                icon -> pixbuf = pixbuf;

                return icon -> pixbuf;
            }
            else
                return NULL;
        }

        list_tmp = list_tmp -> next;
    }

    if ( gsb_select_icon_new_account_icon_from_file ( account_number, filename ) )
        return gsb_select_icon_get_account_pixbuf ( account_number );
    else
        return NULL;
}
