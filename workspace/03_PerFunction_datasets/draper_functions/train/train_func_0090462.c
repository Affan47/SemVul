netsnmp_reassign_requests(netsnmp_agent_session *asp)
{


    int             i;


    netsnmp_tree_cache *old_treecache = asp->treecache;


    asp->treecache =
        (netsnmp_tree_cache *) calloc(asp->treecache_len,
                                      sizeof(netsnmp_tree_cache));

    if (asp->treecache == NULL)
        return SNMP_ERR_GENERR;

    asp->treecache_num = -1;
    if (asp->cache_store) {
        netsnmp_free_cachemap(asp->cache_store);
        asp->cache_store = NULL;
    }

    for (i = 0; i < asp->vbcount; i++) {
        if (asp->requests[i].requestvb == NULL) {


            continue;
        }
        if (asp->requests[i].requestvb->type == ASN_NULL) {
            if (!netsnmp_add_varbind_to_cache(asp, asp->requests[i].index,
                                              asp->requests[i].requestvb,
                                              asp->requests[i].subtree->next)) {
                SNMP_FREE(old_treecache);
            }
        } else if (asp->requests[i].requestvb->type == ASN_PRIV_RETRY) {


            asp->requests[i].requestvb->type = ASN_NULL;
            if (!netsnmp_add_varbind_to_cache(asp, asp->requests[i].index,
                                              asp->requests[i].requestvb,
                                              asp->requests[i].subtree)) {
                SNMP_FREE(old_treecache);
            }
        }
    }

    SNMP_FREE(old_treecache);
    return SNMP_ERR_NOERROR;
}
