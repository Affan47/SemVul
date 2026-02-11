nss_init_connection_ctx(conn_rec *c)
{
    SSLConnRec *sslconn = myConnConfig(c);

    if (sslconn) {
        return sslconn;
    }

    sslconn = apr_pcalloc(c->pool, sizeof(*sslconn));

    sslconn->is_proxy = 0;
    sslconn->disabled = 0;
    sslconn->non_nss_request = 0;
    sslconn->ssl = NULL;

    myConnConfigSet(c, sslconn);

    return sslconn;
}
