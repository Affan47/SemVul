http_use_proxy(Octstr *hostname, int port, int ssl, List *exceptions,
    	    	    Octstr *username, Octstr *password, Octstr *exceptions_regex)
{
    Octstr *e;
    int i;

    gw_assert(run_status == running);
    gw_assert(hostname != NULL);
    gw_assert(octstr_len(hostname) > 0);
    gw_assert(port > 0);

    http_close_proxy();
    mutex_lock(proxy_mutex);

    proxy_hostname = octstr_duplicate(hostname);
    proxy_port = port;
    proxy_ssl = ssl;
    proxy_exceptions = gwlist_create();
    for (i = 0; i < gwlist_len(exceptions); ++i) {
        e = gwlist_get(exceptions, i);
        debug("gwlib.http", 0, "HTTP: Proxy exception `%s'.", octstr_get_cstr(e));
        gwlist_append(proxy_exceptions, octstr_duplicate(e));
    }
    if (exceptions_regex != NULL &&
        (proxy_exceptions_regex = gw_regex_comp(exceptions_regex, REG_EXTENDED)) == NULL)
            panic(0, "Could not compile pattern '%s'", octstr_get_cstr(exceptions_regex));
    proxy_username = octstr_duplicate(username);
    proxy_password = octstr_duplicate(password);
    debug("gwlib.http", 0, "Using proxy <%s:%d> with %s scheme",
    	  octstr_get_cstr(proxy_hostname), proxy_port,
    	  (proxy_ssl ? "HTTPS" : "HTTP"));

    mutex_unlock(proxy_mutex);
}
