gsb_assistant_change_page ( GtkNotebook * notebook, GtkNotebookPage * npage,
				     gint page, gpointer assistant )
{
    typedef gboolean ( * gsb_assistant_callback ) ( GtkWidget *, gint );
    gsb_assistant_callback callback;


    gchar* tmpstr = g_strdup_printf ( "enter%d", page );
    callback = ( gsb_assistant_callback ) g_object_get_data ( G_OBJECT (assistant), tmpstr );
    g_free ( tmpstr );

    if ( callback )
    {
	return callback ( assistant, page );
    }

    return FALSE;
}
