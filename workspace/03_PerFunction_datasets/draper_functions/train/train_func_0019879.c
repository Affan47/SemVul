mkDatetime(xmlrpc_env *    const envP,
           const char *    const value,
           xmlrpc_value ** const valPP) {

    xmlrpc_value * valP;

    createXmlrpcValue(envP, &valP);

    if (!envP->fault_occurred) {
        valP->_type = XMLRPC_TYPE_DATETIME;

        XMLRPC_TYPED_MEM_BLOCK_INIT(
            char, envP, &valP->_block, strlen(value) + 1);
        if (!envP->fault_occurred) {
            char * const contents =
                XMLRPC_TYPED_MEM_BLOCK_CONTENTS(char, &valP->_block);
            strcpy(contents, value);
        }
        if (envP->fault_occurred)
            free(valP);
    }
    *valPP = valP;
}
