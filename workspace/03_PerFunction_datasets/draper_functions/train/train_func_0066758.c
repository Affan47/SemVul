gnc_module_check_loaded(const char * module_name, gint iface)
{
    GNCModuleInfo * modinfo = gnc_module_locate(module_name, iface);
    GList * modules = NULL;
    GList * p = NULL;
    GNCLoadedModule * rv = NULL;

    if (modinfo == NULL)
    {
        return NULL;
    }

    if (!loaded_modules)
    {
        gnc_module_system_init();
    }


    g_hash_table_foreach(loaded_modules, list_loaded, &modules);


    for (p = modules; p; p = p->next)
    {
        GNCLoadedModule * lm = p->data;
        if (!strcmp(lm->filename, modinfo->module_filepath))
        {
            rv = lm;
            break;
        }
    }
    g_list_free(modules);
    return rv;
}
