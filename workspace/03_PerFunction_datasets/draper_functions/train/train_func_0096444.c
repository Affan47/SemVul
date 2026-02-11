conf_string( GHashTable *conf, const gchar *key ) {
    gchar *val = g_hash_table_lookup( conf, key );
    g_assert( key != NULL );
    g_assert( conf != NULL );
    if (val == NULL)
	g_warning("Missing required configuration directive '%s'", key);
    return val;
}
