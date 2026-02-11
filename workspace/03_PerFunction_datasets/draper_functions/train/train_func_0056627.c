check_required_components_helper (const char *component,
                                  const char *app_path,
                                  gpointer    user_data)
{
        gboolean *error = user_data;

        if (app_path == NULL) {
                g_warning ("Unable to find required component '%s'", component);
                *error = TRUE;
        }
}
