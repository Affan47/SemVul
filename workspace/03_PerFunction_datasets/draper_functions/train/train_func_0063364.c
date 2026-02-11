xmlrpc_struct_new(xmlrpc_env* env)
{
    xmlrpc_value *strct;
    int strct_valid;

    XMLRPC_ASSERT_ENV_OK(env);


    strct_valid = 0;


    strct = (xmlrpc_value*) malloc(sizeof(xmlrpc_value));
    XMLRPC_FAIL_IF_NULL(strct, env, XMLRPC_INTERNAL_ERROR,
                        "Could not allocate memory for struct");
    strct->_refcount = 1;
    strct->_type = XMLRPC_TYPE_STRUCT;
    XMLRPC_MEMBLOCK_INIT(_struct_member, env, &strct->_block, 0);
    XMLRPC_FAIL_IF_FAULT(env);
    strct_valid = 1;

 cleanup:
    if (env->fault_occurred) {
        if (strct) {
            if (strct_valid)
                xmlrpc_DECREF(strct);
            else
                free(strct);
        }
        return NULL;
    }
    return strct;
}
