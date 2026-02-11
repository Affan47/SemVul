libgncmod_ofx_gnc_module_init(int refcount)
{
    if (!gnc_module_load("gnucash/engine", 0))
    {
        return FALSE;
    }
    if (!gnc_module_load("gnucash/app-utils", 0))
    {
        return FALSE;
    }
    if (!gnc_module_load("gnucash/gnome-utils", 0))
    {
        return FALSE;
    }
    if (!gnc_module_load("gnucash/import-export", 0))
    {
        return FALSE;
    }


    gnc_plugin_ofx_create_plugin();

    return TRUE;
}
