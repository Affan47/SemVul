snmp_sess_close(void *sessp)
{
    struct session_list *slp = (struct session_list *) sessp;
    netsnmp_transport *transport;
    struct snmp_internal_session *isp;
    netsnmp_session *sesp = NULL;
    struct snmp_secmod_def *sptr;

    if (slp == NULL) {
        return 0;
    }

    if (slp->session != NULL &&
        (sptr = find_sec_mod(slp->session->securityModel)) != NULL &&
        sptr->session_close != NULL) {
        (*sptr->session_close) (slp->session);
    }

    isp = slp->internal;
    slp->internal = NULL;

    if (isp) {
        netsnmp_request_list *rp, *orp;

        SNMP_FREE(isp->packet);


        rp = isp->requests;
        while (rp) {
            orp = rp;
            rp = rp->next_request;
            if (orp->callback) {
                orp->callback(NETSNMP_CALLBACK_OP_TIMED_OUT,
                              slp->session, orp->pdu->reqid,
                              orp->pdu, orp->cb_data);
            }
            snmp_free_pdu(orp->pdu);
            free((char *) orp);
        }

        free((char *) isp);
    }

    transport = slp->transport;
    slp->transport = NULL;

    if (transport) {
        transport->f_close(transport);
        netsnmp_transport_free(transport);
    }

    sesp = slp->session;
    slp->session = NULL;


    if (sesp != NULL && sesp->subsession != NULL) {
        netsnmp_session *subsession = sesp->subsession, *tmpsub;

        while (subsession != NULL) {
            DEBUGMSGTL(("snmp_sess_close",
                        "closing session %p, subsession %p\n", sesp,
                        subsession));
            tmpsub = subsession->next;
            snmp_free_session(subsession);
            subsession = tmpsub;
        }
    }

    snmp_free_session(sesp);
    free((char *) slp);
    return 1;
}
