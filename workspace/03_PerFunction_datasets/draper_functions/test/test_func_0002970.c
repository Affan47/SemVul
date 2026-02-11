http_parse_header (http_request *h, gchar *req) {
    GHashTable *head = g_hash_new();
    gchar **lines, **items, *key, *val, *p;
    guint i;

    lines = g_strsplit( req, "\r\n", 0 );
    items = g_strsplit( lines[0], " ", 3 );

    h->method = g_strdup( items[0] );
    h->uri    = g_strdup( items[1] );


    g_strfreev( items );

    for (i = 1; lines[i] != NULL && lines[i][0] != '\0'; i++ ) {
	key = lines[i];
	val = strchr(key, ':');
	if (val != NULL) {

	    *val = '\0';


	    for (p = key + 1; *p != '\0'; p++)
		*p = tolower(*p);


	    g_strchomp( val += 2 );

	    g_debug("Header in: %s=%s", key, val );
	    g_hash_set( head, key, val );
	}
    }

    g_strfreev( lines );
    h->header = head;
    return head;
}
