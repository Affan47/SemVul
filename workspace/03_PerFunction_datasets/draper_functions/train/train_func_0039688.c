load_modules(krb5_context context)
{
    krb5_error_code ret;
    struct ccselect_module_handle **list = NULL, *handle;
    krb5_plugin_initvt_fn *modules = NULL, *mod;
    size_t count;

#ifndef _WIN32
    ret = k5_plugin_register(context, PLUGIN_INTERFACE_CCSELECT, "k5identity",
                             ccselect_k5identity_initvt);
    if (ret != 0)
        goto cleanup;
#endif

    ret = k5_plugin_register(context, PLUGIN_INTERFACE_CCSELECT, "realm",
                             ccselect_realm_initvt);
    if (ret != 0)
        goto cleanup;

    ret = k5_plugin_load_all(context, PLUGIN_INTERFACE_CCSELECT, &modules);
    if (ret != 0)
        goto cleanup;


    for (count = 0; modules[count] != NULL; count++);
    list = k5calloc(count + 1, sizeof(*list), &ret);
    if (list == NULL)
        goto cleanup;


    count = 0;
    for (mod = modules; *mod != NULL; mod++) {
        handle = k5alloc(sizeof(*handle), &ret);
        if (handle == NULL)
            goto cleanup;
        ret = (*mod)(context, 1, 1, (krb5_plugin_vtable)&handle->vt);
        if (ret != 0) {
            TRACE_CCSELECT_VTINIT_FAIL(context, ret);
            free(handle);
            continue;
        }
        handle->data = NULL;
        ret = handle->vt.init(context, &handle->data, &handle->priority);
        if (ret != 0) {
            TRACE_CCSELECT_INIT_FAIL(context, handle->vt.name, ret);
            free(handle);
            continue;
        }
        list[count++] = handle;
        list[count] = NULL;
    }
    list[count] = NULL;

    ret = 0;
    context->ccselect_handles = list;
    list = NULL;

cleanup:
    k5_plugin_free_modules(context, modules);
    free_handles(context, list);
    return ret;
}
