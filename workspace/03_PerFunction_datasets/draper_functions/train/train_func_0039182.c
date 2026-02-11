xmlrpc_add_element(XMLRPCValue *xrarray, XMLRPCValue *value)
{
    if (xrarray == NULL || xrarray->v_type != xr_array || value == NULL)
        return -1;

    gwlist_produce(xrarray->v_array, value);
    return 1;
}
