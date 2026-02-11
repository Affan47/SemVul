pagedresults_in_use_nolock(Connection *conn)
{
    LDAPDebug0Args(LDAP_DEBUG_TRACE, "--> pagedresults_in_use\n");
    if (NULL == conn) {
        LDAPDebug0Args(LDAP_DEBUG_TRACE, "<-- pagedresults_in_use: -\n");
        return 0;
    }
    LDAPDebug1Arg(LDAP_DEBUG_TRACE, "<-- pagedresults_in_use: %d\n",
                  conn->c_pagedresults.prl_count);
    return conn->c_pagedresults.prl_count;
}
