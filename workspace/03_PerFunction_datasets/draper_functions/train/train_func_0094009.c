gnc_html_unregister_object_handler( const gchar* classid )
{
    gchar* keyptr = NULL;
    gchar* valptr = NULL;
    gchar** p_keyptr = &keyptr;
    gchar** p_valptr = &valptr;
    gchar* lc_id = g_ascii_strdown (classid, -1);

    if ( g_hash_table_lookup_extended( gnc_html_object_handlers,
                                       lc_id,
                                       (gpointer *)p_keyptr,
                                       (gpointer *)p_valptr) )
    {
        g_hash_table_remove( gnc_html_object_handlers, lc_id );
        g_free( keyptr );
    }
    g_free( lc_id );
}
