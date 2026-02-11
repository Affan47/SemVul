dispatch_call(xmlrpc_env *      const envP,
              xmlrpc_registry * const registryP,
              const char *      const methodName,
              xmlrpc_value *    const paramArrayP,
              xmlrpc_value **   const resultPP) {

    callPreinvokeMethodIfAny(envP, registryP, methodName, paramArrayP);
    if (!envP->fault_occurred) {
        xmlrpc_value * method_info;


        xmlrpc_struct_find_value(envP, registryP->_methods,
                                 methodName, &method_info);
        if (!envP->fault_occurred) {
            if (method_info)
                callNamedMethod(envP, method_info, paramArrayP, resultPP);
            else {
                if (registryP->_default_method)
                    callDefaultMethod(envP, registryP->_default_method,
                                      methodName, paramArrayP,
                                      resultPP);
                else {

                    xmlrpc_env_set_fault_formatted(
                        envP, XMLRPC_NO_SUCH_METHOD_ERROR,
                        "Method '%s' not defined", methodName);
                }
            }
        }
    }

    if (envP->fault_occurred)
        *resultPP = NULL;
}
