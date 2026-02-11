cddb_set_http_proxy_credentials(cddb_conn_t* c,
                                     const char *username, const char* password)
{

    FREE_NOT_NULL(c->http_proxy_username);
    FREE_NOT_NULL(c->http_proxy_password);

    cddb_set_http_proxy_auth(c, username, password);
}
