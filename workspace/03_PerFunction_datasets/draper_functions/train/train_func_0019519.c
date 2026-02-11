replica_cleanallruv_replica_alive(Repl_Agmt *agmt)
{
    Repl_Connection *conn = NULL;
    LDAP *ld = NULL;
    LDAPMessage *result = NULL;
    int rc = -1;

    if((conn = conn_new(agmt)) == NULL){
        return rc;
    }
    if(conn_connect(conn) == CONN_OPERATION_SUCCESS){
        ld = conn_get_ldap(conn);
        if(ld == NULL){
            slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name, "CleanAllRUV_task: failed to get LDAP "
                "handle from the replication agmt (%s).  Moving on to the next agmt.\n",agmt_get_long_name(agmt));
            conn_delete_internal_ext(conn);
            return -1;
        }
        if(ldap_search_ext_s(ld, "", LDAP_SCOPE_BASE, "objectclass=top",
            NULL, 0, NULL, NULL, NULL, 0, &result) == LDAP_SUCCESS)
        {
            rc = 0;
        } else {
            rc = -1;
        }
        if(result)
            ldap_msgfree( result );
    }
    conn_delete_internal_ext(conn);

    return rc;
}
