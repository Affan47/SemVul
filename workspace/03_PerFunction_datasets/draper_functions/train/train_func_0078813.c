snmp_close(netsnmp_session * session)
{
    struct session_list *slp = NULL, *oslp = NULL;

    {
        snmp_res_lock(MT_LIBRARY_ID, MT_LIB_SESSION);
        if (Sessions && Sessions->session == session) {
            slp = Sessions;
            Sessions = slp->next;
        } else {
            for (slp = Sessions; slp; slp = slp->next) {
                if (slp->session == session) {
                    if (oslp)
                        oslp->next = slp->next;
                    break;
                }
                oslp = slp;
            }
        }
        snmp_res_unlock(MT_LIBRARY_ID, MT_LIB_SESSION);
    }
    if (slp == NULL) {
        return 0;
    }
    return snmp_sess_close((void *) slp);
}
