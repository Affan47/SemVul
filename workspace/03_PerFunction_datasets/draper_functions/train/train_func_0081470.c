build_url( const gchar *uri, GHashTable *query ) {
    GString *dest = g_string_new( uri );
    g_assert( query != NULL );

    g_string_append( dest, "?" );
    g_hash_table_foreach( query, (GHFunc) build_url_each, dest );
    g_string_erase( dest, dest->len - 1, 1 );

    return dest;
}
