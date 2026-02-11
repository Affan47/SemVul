parse_connect_url(char *src, char *httpv, struct url *url, int so)
{
    char *ss, *host = NULL;

    if (!src)
        return (-1);
    ss = strchr(src, ':');
    if (!ss) {
        say_bad_request(so, "Bad request, no proto:", src, ERR_BAD_URL, NULL);
        return (-1);
    }
    *ss = 0;
    host = xmalloc(strlen(src) + 1, "parse_connect_url():");
    if (!host)
        goto err;
    memcpy_to_lower(host, src, strlen(src) + 1);
    url->host = host;
    url->port = atoi(ss + 1);
    goto done;
  err:
    *ss = ':';
    if (host)
        xfree(host);
    return (-1);
  done:
    *ss = ':';
    return (0);
}
