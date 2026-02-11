dav_xmlns_add_uri(dav_xmlns_info *xi,
                                            const char *uri)
{
    const char *prefix;

    if ((prefix = apr_hash_get(xi->uri_prefix, uri,
                               APR_HASH_KEY_STRING)) != NULL)
        return prefix;

    prefix = apr_psprintf(xi->pool, "g%d", xi->count++);
    dav_xmlns_add(xi, prefix, uri);
    return prefix;
}
