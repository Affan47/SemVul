target_redirect ( http_request *h ) {
    gchar *orig, *host   = HEADER("Host");

    if ( host != NULL ) {
	orig = g_strdup_printf( "http://%s%s", HEADER("Host"), h->uri );
    } else {
	orig = CONF("HomePage");
    }

    return orig;
}
