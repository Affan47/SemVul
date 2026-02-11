pdu_create_opt_context(int command, const char* context, size_t len)
{
    netsnmp_pdu* res = snmp_pdu_create(command);
    if (res)
        if (context) {
            if (snmp_clone_mem((void**)&res->contextName, context, len)) {
                snmp_free_pdu(res);
                res = NULL;
            } else
                res->contextNameLen = len;
        }
    return res;
}
