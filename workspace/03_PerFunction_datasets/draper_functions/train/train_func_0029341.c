load_double( const GncSqlBackend* be, GncSqlRow* row,
              QofSetterFunc setter, gpointer pObject,
             const GncSqlColumnTableEntry* table_row )
{
    const GValue* val;
    gdouble d_value;

    g_return_if_fail( be != NULL );
    g_return_if_fail( row != NULL );
    g_return_if_fail( pObject != NULL );
    g_return_if_fail( table_row != NULL );
    g_return_if_fail( table_row->gobj_param_name != NULL || setter != NULL );

    val = gnc_sql_row_get_value_at_col_name( row, table_row->col_name );
    if ( val == NULL )
    {
        (*setter)( pObject, (gpointer)NULL );
    }
    else
    {
        if ( G_VALUE_HOLDS(val, G_TYPE_INT) )
        {
            d_value = (gdouble)g_value_get_int( val );
        }
        else if ( G_VALUE_HOLDS(val, G_TYPE_FLOAT) )
        {
            d_value = g_value_get_float( val );
        }
        else if (G_VALUE_HOLDS(val, G_TYPE_DOUBLE) )
        {
            d_value = g_value_get_double( val );
        }
        else
        {
            PWARN( "Unknown float value type: %s\n", g_type_name( G_VALUE_TYPE(val) ) );
            d_value = 0;
        }
        if ( table_row->gobj_param_name != NULL )
        {
            g_object_set( pObject, table_row->gobj_param_name, d_value, NULL );
        }
        else
        {
            (*setter)( pObject, (gpointer)&d_value );
        }
    }
}
