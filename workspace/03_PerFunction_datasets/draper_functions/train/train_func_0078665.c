append_required_components_helper (const char *component,
                                   const char *app_path,
                                   gpointer    user_data)
{
        GsmManager *manager = user_data;

        if (app_path == NULL)
                g_warning ("Unable to find required component '%s'", component);
        else
                gsm_manager_add_required_app (manager, app_path, NULL);
}
