snmpv3_probe_contextEngineID_rfc5343(void *slp, netsnmp_session *session) {
    netsnmp_pdu    *pdu = NULL, *response = NULL;
    static oid      snmpEngineIDoid[]   = { 1,3,6,1,6,3,10,2,1,1,0};
    static size_t   snmpEngineIDoid_len = 11;

    static char     probeEngineID[] = { (char)0x80, 0, 0, 0, 6 };
    static size_t   probeEngineID_len = sizeof(probeEngineID);

    int status;

    pdu = snmp_pdu_create(SNMP_MSG_GET);
    if (!pdu)
        return SNMP_ERR_GENERR;
    pdu->version = SNMP_VERSION_3;

    if (session->securityName) {
        pdu->securityName = strdup(session->securityName);
        pdu->securityNameLen = strlen(pdu->securityName);
    }
    pdu->securityLevel = SNMP_SEC_LEVEL_NOAUTH;
    pdu->securityModel = session->securityModel;
    if (memdup(&pdu->contextEngineID, probeEngineID, probeEngineID_len) !=
        SNMPERR_SUCCESS) {
        snmp_log(LOG_ERR, "failed to clone memory for rfc5343 probe\n");
        snmp_free_pdu(pdu);
        return SNMP_ERR_GENERR;
    }
    pdu->contextEngineIDLen = probeEngineID_len;

    snmp_add_null_var(pdu, snmpEngineIDoid, snmpEngineIDoid_len);

    DEBUGMSGTL(("snmp_api", "probing for engineID using rfc5343 methods...\n"));
    session->flags |= SNMP_FLAGS_DONT_PROBE;
    status = snmp_sess_synch_response(slp, pdu, &response);

    if ((response == NULL) || (status != STAT_SUCCESS)) {
        snmp_log(LOG_ERR, "failed rfc5343 contextEngineID probing\n");
        return SNMP_ERR_GENERR;
    }


    if (NULL != response->variables &&
        NULL != response->variables->name &&
        snmp_oid_compare(response->variables->name,
                         response->variables->name_length,
                         snmpEngineIDoid, snmpEngineIDoid_len) == 0 &&
        ASN_OCTET_STR == response->variables->type  &&
        NULL != response->variables->val.string &&
        response->variables->val_len > 0) {
        if (memdup(&session->contextEngineID,
                   response->variables->val.string,
                   response->variables->val_len) != SNMPERR_SUCCESS) {
            snmp_log(LOG_ERR, "failed rfc5343 contextEngineID probing: memory allocation failed\n");
            return SNMP_ERR_GENERR;
        }


        if (memdup(&session->securityEngineID,
                   response->variables->val.string,
                   response->variables->val_len) != SNMPERR_SUCCESS) {
            snmp_log(LOG_ERR, "failed rfc5343 securityEngineID probing: memory allocation failed\n");
            return SNMP_ERR_GENERR;
        }

        session->securityEngineIDLen = session->contextEngineIDLen =
            response->variables->val_len;

        if (snmp_get_do_debugging()) {
            size_t i;
            DEBUGMSGTL(("snmp_sess_open",
                        "  probe found engineID:  "));
            for (i = 0; i < session->securityEngineIDLen; i++)
                DEBUGMSG(("snmp_sess_open", "%02x",
                          session->securityEngineID[i]));
            DEBUGMSG(("snmp_sess_open", "\n"));
        }
    }
    return SNMPERR_SUCCESS;
}
