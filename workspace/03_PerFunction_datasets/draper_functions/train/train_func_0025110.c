CONTAINER_INSERT_HELPER(netsnmp_container* x, const void* k)
{
    while(x && x->insert_filter && x->insert_filter(x,k) == 1)
        x = x->next;
    if(x) {
        int rc = x->insert(x,k);
        if(rc)
            snmp_log(LOG_DEBUG,"error on subcontainer '%s' insert (%d)\n",
                     x->container_name ? x->container_name : "", rc);
        else {
            rc = CONTAINER_INSERT_HELPER(x->next, k);
            if(rc)
                x->remove(x,k);
        }
        return rc;
    }
    return 0;
}
