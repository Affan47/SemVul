clientCallServerParams(xmlrpc_env *             const envP,
                       struct clientTransport * const transportP,
                       xmlrpc_server_info *     const serverP,
                       const char *             const methodName,
                       xmlrpc_value *           const paramArrayP,
                       xmlrpc_value **          const resultPP) {

    call_info * callInfoP;

    if (!clientInitialized)
        xmlrpc_env_set_fault_formatted(
            envP, XMLRPC_INTERNAL_ERROR,
            "Xmlrpc-c client instance has not been initialized "
            "(need to call xmlrpc_client_init2()).");
    else {
        call_info_new(envP, serverP, methodName, paramArrayP, &callInfoP);
        if (!envP->fault_occurred) {
            xmlrpc_mem_block * respXmlP;

            clientTransportOps.call(envP, transportP, serverP,
                                    callInfoP->serialized_xml, callInfoP,
                                    &respXmlP);
            if (!envP->fault_occurred) {
                xmlrpc_traceXml("XML-RPC RESPONSE",
                                XMLRPC_MEMBLOCK_CONTENTS(char, respXmlP),
                                (unsigned int)XMLRPC_MEMBLOCK_SIZE(char, respXmlP));

                *resultPP = xmlrpc_parse_response(
                    envP,
                    XMLRPC_MEMBLOCK_CONTENTS(char, respXmlP),
                    XMLRPC_MEMBLOCK_SIZE(char, respXmlP));
                XMLRPC_MEMBLOCK_FREE(char, respXmlP);
            }
            call_info_free(callInfoP);
        }
    }
}
