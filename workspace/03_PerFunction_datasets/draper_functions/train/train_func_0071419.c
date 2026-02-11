plugin_system_cleanup(void)
{
    plugin_registry_save ();

    for (GList * node = loaded_modules; node != NULL; node = node->next)
        plugin2_unload (node->data);

    g_list_free (loaded_modules);
    loaded_modules = NULL;

    audgui_cleanup ();
}
