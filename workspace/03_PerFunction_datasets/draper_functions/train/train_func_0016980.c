set_string_val( gpointer pObject,  gpointer pValue )
{
    slot_info_t* pInfo = (slot_info_t*)pObject;
    KvpValue *value = NULL;

    g_return_if_fail( pObject != NULL );

    if ( pInfo->value_type != KVP_TYPE_STRING || pValue == NULL ) return;
    value = kvp_value_new_string( (gchar*)pValue );
    set_slot_from_value( pInfo, value );
}
