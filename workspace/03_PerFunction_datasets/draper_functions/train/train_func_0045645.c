xmlrpc_response_add_param(XMLRPCMethodResponse *response, XMLRPCValue *value)
{
    if (response == NULL || value == NULL)
        return -1;

    if (response->param != NULL) {
        error(0, "XMLRPC: Method Response may contain only one param.");
        return -1;
    }
    if (response->fault != NULL) {
        error(0, "XMLRPC: Fault Response may not contain any param.");
        return -1;
    }

    response->param = value;
    return 0;
}
