authdaemon_verify_password(sasl_conn_t *conn,
				      const char *userid,
				      const char *passwd,
				      const char *service,
				      const char *user_realm __attribute__((unused)))
{
    const char *p = NULL;
    sasl_getopt_t *getopt;
    void *context;
    int result = SASL_FAIL;
    char *query = NULL;
    int sock = -1;


    if (_sasl_getcallback(conn, SASL_CB_GETOPT, &getopt, &context) == SASL_OK) {
	getopt(context, NULL, "authdaemond_path", &p, NULL);
    }
    if (!p) {


	p = PATH_AUTHDAEMON_SOCKET;
    }

    if ((sock = authdaemon_connect(conn, p)) < 0)
	goto out;
    if (!(query = authdaemon_build_query(service, "login", userid, passwd)))
	goto out;
    result = authdaemon_talk(conn, sock, query);
out:
    if (sock >= 0)
	close(sock), sock = -1;
    if (query)
	sasl_FREE(query), query = 0;
    return result;
}
