collect(void *  const ptr,
        size_t  const size,
        size_t  const nmemb,
        FILE  * const stream) {


    xmlrpc_mem_block * const responseXmlP = (xmlrpc_mem_block *) stream;
    char * const buffer = ptr;
    size_t const length = nmemb * size;

    size_t retval;
    xmlrpc_env env;

    xmlrpc_env_init(&env);
    xmlrpc_mem_block_append(&env, responseXmlP, buffer, length);
    if (env.fault_occurred)
        retval = (size_t)-1;
    else

        retval = length;

    return retval;
}
