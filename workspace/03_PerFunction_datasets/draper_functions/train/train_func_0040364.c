_retrieve_guid_( gpointer pObject,  gpointer pValue )
{
    GncGUID* pGuid = (GncGUID*)pObject;
    GncGUID* guid = (GncGUID*)pValue;

    g_return_if_fail( pObject != NULL );
    g_return_if_fail( pValue != NULL );

    memcpy( pGuid, guid, sizeof( GncGUID ) );
}
