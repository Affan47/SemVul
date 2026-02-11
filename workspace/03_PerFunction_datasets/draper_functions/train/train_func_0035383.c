snmp_add(netsnmp_session * in_session,
         netsnmp_transport *transport,
         int (*fpre_parse) (netsnmp_session *, netsnmp_transport *, void *,
                            int), int (*fpost_parse) (netsnmp_session *,
                                                      netsnmp_pdu *, int))
{
    struct session_list *slp;
    slp = (struct session_list *) snmp_sess_add_ex(in_session, transport,
                                                   fpre_parse, NULL,
                                                   fpost_parse, NULL, NULL,
                                                   NULL, NULL);
    if (slp == NULL) {
        return NULL;
    }

    snmp_res_lock(MT_LIBRARY_ID, MT_LIB_SESSION);
    slp->next = Sessions;
    Sessions = slp;
    snmp_res_unlock(MT_LIBRARY_ID, MT_LIB_SESSION);

    return (slp->session);
}
