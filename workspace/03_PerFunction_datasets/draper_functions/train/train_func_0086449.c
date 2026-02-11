agentx_remove_agentcaps(netsnmp_session * ss,
                        const oid * agent_cap, size_t agent_caplen)
{
    netsnmp_pdu    *pdu, *response;

    if (ss == NULL || !IS_AGENTX_VERSION(ss->version)) {
        return 0;
    }

    pdu = snmp_pdu_create(AGENTX_MSG_REMOVE_AGENT_CAPS);
    if (pdu == NULL)
        return 0;
    pdu->time = 0;
    pdu->sessid = ss->sessid;
    snmp_add_null_var(pdu, agent_cap, agent_caplen);

    if (agentx_synch_response(ss, pdu, &response) != STAT_SUCCESS)
        return 0;

    if (response->errstat != SNMP_ERR_NOERROR) {
        snmp_free_pdu(response);
        return 0;
    }

    snmp_free_pdu(response);
    return 1;
}
