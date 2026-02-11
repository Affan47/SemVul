add_gvalue_guid_to_slist( const GncSqlBackend* be, QofIdTypeConst obj_name,
                          const gpointer pObject, const GncSqlColumnTableEntry* table_row, GSList** pList )
{
    QofAccessFunc getter;
    GncGUID* guid = NULL;
    gchar guid_buf[GUID_ENCODING_LENGTH+1];
    GValue* value;

    g_return_if_fail( be != NULL );
    g_return_if_fail( obj_name != NULL );
    g_return_if_fail( pObject != NULL );
    g_return_if_fail( table_row != NULL );

    value = g_new0( GValue, 1 );
    g_assert( value != NULL );
    if ( table_row->gobj_param_name != NULL )
    {
        g_object_get( pObject, table_row->gobj_param_name, &guid, NULL );
    }
    else
    {
        getter = gnc_sql_get_getter( obj_name, table_row );
        if ( getter != NULL )
        {
            guid = (*getter)( pObject, NULL );
        }
    }
    (void)g_value_init( value, G_TYPE_STRING );
    if ( guid != NULL )
    {
        (void)guid_to_string_buff( guid, guid_buf );
        g_value_set_string( value, guid_buf );
    }

    (*pList) = g_slist_append( (*pList), value );

}
