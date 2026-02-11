pagedresults_set_with_sort(Connection *conn, Operation *op,
                           int flags, int index)
{
    int rc = -1;
    if (!op_is_pagedresults(op)) {
        return rc;
    }
    LDAPDebug1Arg(LDAP_DEBUG_TRACE,
                  "--> pagedresults_set_with_sort: idx=%d\n", index);
    if (conn && (index > -1)) {
        PR_Lock(conn->c_mutex);
        if (index < conn->c_pagedresults.prl_maxlen) {
            if (flags & OP_FLAG_SERVER_SIDE_SORTING) {
                conn->c_pagedresults.prl_list[index].pr_flags |=
                                               CONN_FLAG_PAGEDRESULTS_WITH_SORT;
            }
        }
        PR_Unlock(conn->c_mutex);
        rc = 0;
    }
    LDAPDebug1Arg(LDAP_DEBUG_TRACE, "<-- pagedresults_set_with_sort: %d\n", rc);
    return rc;
}
