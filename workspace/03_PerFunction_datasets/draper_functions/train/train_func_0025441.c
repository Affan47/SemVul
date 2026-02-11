unload_module(void *data)
{
    ap_module_symbol_t *modi = (ap_module_symbol_t*)data;


    if (modi->modp == NULL)
        return APR_SUCCESS;


    ap_remove_loaded_module(modi->modp);


    modi->modp = NULL;
    modi->name = NULL;
    return APR_SUCCESS;
}
