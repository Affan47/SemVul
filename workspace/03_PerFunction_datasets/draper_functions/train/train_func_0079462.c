globus_extension_register_builtin(
    const char *                        extension_name,
    globus_module_descriptor_t *        module_descriptor)
{
    globus_l_extension_builtin_t *      builtin;
    GlobusFuncName(globus_extension_register_builtin);

    GlobusExtensionDebugEnterSymbol(extension_name);

    builtin = (globus_l_extension_builtin_t *)
        globus_malloc(sizeof(globus_l_extension_builtin_t));
    if(!builtin)
    {
        goto error_alloc;
    }

    builtin->owner = (globus_l_extension_module_t *)
        globus_thread_getspecific(globus_l_extension_owner_key);
    builtin->module = module_descriptor;
    builtin->extension_name = globus_libc_strdup(extension_name);
    if(!builtin->extension_name)
    {
        goto error_strdup;
    }

    globus_rmutex_lock(&globus_l_extension_mutex);
    {
        int                             rc;

        rc = globus_hashtable_insert(
            &globus_l_extension_builtins, builtin->extension_name, builtin);
        if(rc != 0)
        {
            goto error_insert;
        }
    }
    globus_rmutex_unlock(&globus_l_extension_mutex);

    GlobusExtensionDebugExit();
    return GLOBUS_SUCCESS;

error_insert:
    globus_rmutex_unlock(&globus_l_extension_mutex);
    globus_free(builtin->extension_name);
error_strdup:
    globus_free(builtin);
error_alloc:
    GlobusExtensionDebugExitWithError();
    return GLOBUS_FAILURE;
}
