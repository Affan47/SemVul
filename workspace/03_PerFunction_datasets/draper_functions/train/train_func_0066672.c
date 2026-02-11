get_obj_guid( gpointer pObject )
{
    recurrence_info_t* pInfo = (recurrence_info_t*)pObject;

    g_return_val_if_fail( pObject != NULL, NULL );

    return (gpointer)pInfo->guid;
}
