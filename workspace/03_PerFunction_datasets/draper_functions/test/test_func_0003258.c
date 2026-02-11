set_path( gpointer pObject,  gpointer pValue )
{
    slot_info_t* pInfo = (slot_info_t*)pObject;

    g_return_if_fail( pObject != NULL );
    g_return_if_fail( pValue != NULL );

    if ( pInfo->path != NULL )
    {
        (void)g_string_free( pInfo->path, TRUE );
    }
    pInfo->path = g_string_new( (gchar*)pValue );
}
