netsnmp_iquery_pdu_session(netsnmp_pdu* pdu) {
    if (!pdu)
       return NULL;
    if (pdu->version == SNMP_VERSION_3)
        return netsnmp_iquery_session( pdu->securityName,
                           pdu->version,
                           pdu->securityModel,
                           pdu->securityLevel,
                           pdu->securityEngineID,
                           pdu->securityEngineIDLen);
    else
        return netsnmp_iquery_session((char *) pdu->community,
                           pdu->version,
                           pdu->version+1,
                           SNMP_SEC_LEVEL_NOAUTH,
                           pdu->securityEngineID,
                           pdu->securityEngineIDLen);
}
