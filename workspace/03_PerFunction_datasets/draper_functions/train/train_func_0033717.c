gnc_sql_get_integer_value( const GValue* value )
{
    g_return_val_if_fail( value != NULL, 0 );

    if ( G_VALUE_HOLDS_INT(value) )
    {
        return (gint64)g_value_get_int( value );
    }
    else if ( G_VALUE_HOLDS_UINT(value) )
    {
        return (gint64)g_value_get_uint( value );
    }
    else if ( G_VALUE_HOLDS_LONG(value) )
    {
        return (gint64)g_value_get_long( value );
    }
    else if ( G_VALUE_HOLDS_ULONG(value) )
    {
        return (gint64)g_value_get_ulong( value );
    }
    else if ( G_VALUE_HOLDS_INT64(value) )
    {
        return g_value_get_int64( value );
    }
    else if ( G_VALUE_HOLDS_UINT64(value) )
    {
        return (gint64)g_value_get_uint64( value );
    }
    else if ( G_VALUE_HOLDS_STRING( value ) )
    {
        return g_ascii_strtoll( g_value_get_string( value ), NULL, 10 );
    }
    else
    {
        PWARN( "Unknown type: %s", G_VALUE_TYPE_NAME( value ) );
    }

    return 0;
}
