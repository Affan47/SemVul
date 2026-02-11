orte_app_context_destructor(orte_app_context_t* app_context)
{
    opal_list_item_t *item;
    int i;
    orte_proc_t *proc;

    if (NULL != app_context->app) {
        free (app_context->app);
        app_context->app = NULL;
    }

    for (i=0; i < app_context->procs.size; i++) {
        if (NULL != (proc = (orte_proc_t*)opal_pointer_array_get_item(&app_context->procs, i))) {
            OBJ_RELEASE(proc);
        }
    }
    OBJ_DESTRUCT(&app_context->procs);


    if (NULL != app_context->argv) {
        opal_argv_free(app_context->argv);
        app_context->argv = NULL;
    }

    if (NULL != app_context->env) {
        opal_argv_free(app_context->env);
        app_context->env = NULL;
    }

    if (NULL != app_context->cwd) {
        free (app_context->cwd);
        app_context->cwd = NULL;
    }

    if (NULL != app_context->hostfile) {
        free(app_context->hostfile);
        app_context->hostfile = NULL;
    }

    if (NULL != app_context->add_hostfile) {
        free(app_context->add_hostfile);
        app_context->add_hostfile = NULL;
    }

    if (NULL != app_context->add_host) {
        opal_argv_free(app_context->add_host);
        app_context->add_host = NULL;
    }

    if (NULL != app_context->dash_host) {
        opal_argv_free(app_context->dash_host);
        app_context->dash_host = NULL;
    }

    while (NULL != (item = opal_list_remove_first(&app_context->resource_constraints))) {
        OBJ_RELEASE(item);
    }
    OBJ_DESTRUCT(&app_context->resource_constraints);

    if (NULL != app_context->prefix_dir) {
        free(app_context->prefix_dir);
        app_context->prefix_dir = NULL;
    }

    app_context->preload_binary = false;

    if(NULL != app_context->preload_files) {
        free(app_context->preload_files);
        app_context->preload_files = NULL;
    }

#if OPAL_ENABLE_FT_CR == 1
    if( NULL != app_context->sstore_load ) {
        free(app_context->sstore_load);
        app_context->sstore_load = NULL;
    }
#endif
}
