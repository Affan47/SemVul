dav_propdb_define_namespaces(dav_db *db, dav_xmlns_info *xi)
{
    int ns;
    const char *uri = db->ns_table.buf + sizeof(dav_propdb_metadata);


    for (ns = 0; ns < db->ns_count; ++ns, uri += strlen(uri) + 1) {


        if (*uri == '\0')
            continue;


        dav_xmlns_add(xi,
                      apr_psprintf(xi->pool, "ns%d", ns),
                      apr_pstrdup(xi->pool, uri));
    }

    return NULL;
}
