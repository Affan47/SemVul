webauthldap_dosearch(MWAL_LDAP_CTXT* lc)
{
    LDAPMessage *res = NULL;
    LDAPMessage *msg = NULL;
    ber_int_t msgid;
    int rc, numMessages;
    int attrsonly = 0;

    rc = ldap_search_ext(lc->ld, lc->sconf->base, lc->sconf->scope, lc->filter,
                         lc->attrs, attrsonly, NULL, NULL, NULL,
                         LDAP_SIZELIMIT, &msgid);

    if (rc != LDAP_SUCCESS) {
        if (rc == LDAP_SERVER_DOWN || rc == LDAP_CONNECT_ERROR) {
            if (lc->sconf->debug)
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, lc->r->server,
                            "webauthldap(%s): timeout during ldap_search_ext: %s (%d)",
                             lc->r->user, ldap_err2string(rc), rc);
            return HTTP_SERVICE_UNAVAILABLE;
        } else {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, lc->r->server,
                         "webauthldap(%s): ldap_search_ext: %s (%d)",
                         lc->r->user, ldap_err2string(rc), rc);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    if ((rc =
         ldap_result(lc->ld, LDAP_RES_ANY, LDAP_MSG_ALL, NULL, &res)) > 0) {

        numMessages = ldap_count_messages(lc->ld, res);

        if (lc->sconf->debug)
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, lc->r->server,
                         "webauthldap(%s): search returned %d messages",
                         lc->r->user, numMessages);

        if (numMessages > 0) {
            lc->entries = (apr_table_t **)
                apr_pcalloc(lc->r->pool,
                            (numMessages+1)*sizeof(apr_table_t *));
            lc->numEntries = 0;
            for (msg = ldap_first_message(lc->ld, res);
                 msg != NULL; msg = ldap_next_message(lc->ld, msg)) {

                if (ldap_msgtype(msg) == LDAP_RES_SEARCH_ENTRY) {
                    lc->entries[lc->numEntries] = apr_table_make(lc->r->pool,
                                                                 50);
                    webauthldap_parse_entry(lc, msg,
                                            lc->entries[lc->numEntries]);
                    lc->numEntries++;
                }
            }
            if (lc->sconf->debug)
                ap_log_error(APLOG_MARK, APLOG_INFO, 0, lc->r->server,
                             "webauthldap(%s): search returned %lu entries",
                             lc->r->user, (unsigned long) lc->numEntries);
        }
        ldap_msgfree(res);
    }

    if ((rc == -1) || (rc == 0)) {
        return HTTP_SERVICE_UNAVAILABLE;
    }


    if (lc->numEntries == 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, lc->r->server,
                     "webauthldap: user %s not found in ldap",
                     lc->r->user);

    return 0;
}
