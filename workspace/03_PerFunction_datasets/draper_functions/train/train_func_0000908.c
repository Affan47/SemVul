xmlrpc_get_element(XMLRPCValue *xrarray, int i)
{
    if (xrarray == NULL || xrarray->v_type != xr_array || i < 0)
        return NULL;

    return gwlist_get(xrarray->v_array, i);
}
