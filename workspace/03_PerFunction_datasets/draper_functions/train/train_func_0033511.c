http_parse_query (http_request *h, gchar *post) {
    gchar *q = NULL;

    g_assert( h != NULL );

    if (h->uri != NULL) {

	q = strchr( h->uri, '?' );
    }

    if (post != NULL) {
	h->query = parse_query_string( post );
    } else if (q != NULL) {
	h->query = parse_query_string( q + 1 );
    } else {
	h->query = NULL;
    }

    if (q != NULL)
	*q = '\0';

    return h->query;
}
