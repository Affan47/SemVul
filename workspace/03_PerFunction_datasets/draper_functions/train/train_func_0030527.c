set_slot_from_value( slot_info_t *pInfo, KvpValue *pValue)
{
    g_return_if_fail( pInfo != NULL );
    g_return_if_fail( pValue != NULL );

    switch ( pInfo->context)
    {
    case FRAME:
    {
        gchar *key = get_key_from_path( pInfo->path );
        kvp_frame_set_value_nc( pInfo->pKvpFrame, key, pValue );
        g_free( key );
        break;
    }
    case LIST:
    {
        pInfo->pList = g_list_append(pInfo->pList, pValue);
        break;
    }
    case NONE:
    default:
    {
        gchar *key = get_key_from_path( pInfo->path );
        gchar *path = get_path_from_path( pInfo->path );
        KvpFrame* frame = pInfo->pKvpFrame;
        if ( path )
        {
            frame = kvp_frame_get_frame_slash( frame, path );
            g_free( path );
        }
        kvp_frame_set_value_nc( frame, key, pValue );
        g_free( key );
        break;
    }
    }
}
