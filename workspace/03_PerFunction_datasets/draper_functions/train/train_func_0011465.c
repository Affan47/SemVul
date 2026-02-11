fw_exec_add_env ( gchar *key, gchar *val, GPtrArray *env ) {
    gchar *p;

    g_assert( key != NULL );
    g_assert( val != NULL );
    p = g_strdup_printf( "%s=%s", key, val );
    g_ptr_array_add( env, p );
}
