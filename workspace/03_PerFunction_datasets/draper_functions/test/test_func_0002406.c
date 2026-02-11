language_support_generate_c_signature (const gchar* separator,
                                       const gchar* widget,
                                       GSignalQuery query,
                                       gboolean swapped,
                                       const gchar* handler)
{
    GList* names = NULL;
    GString* str = g_string_new ("\n");
    const gchar* widget_param = language_support_get_signal_parameter (widget,
                                                                       &names);
    int i;
    g_string_append (str, g_type_name (query.return_type));
    if (!swapped)
        g_string_append_printf (str, "%s%s (%s *%s",
                                     separator, handler, widget, widget_param);
    else
        g_string_append_printf (str, "%s%s (gpointer user_data, %s *%s",
                                     separator, handler, widget, widget_param);

    for (i = 0; i < query.n_params; i++)
    {
        const gchar* type_name = g_type_name (query.param_types[i]);
        if (!type_name) continue;

        const gchar* param_name = language_support_get_signal_parameter (type_name,
                                                                         &names);

        if (query.param_types[i] <= G_TYPE_DOUBLE)
        {
            g_string_append_printf (str, ", %s %s", type_name, param_name);
        }
        else
        {
            g_string_append_printf (str, ", %s *%s", type_name, param_name);
        }
    }
    if (!swapped)
        g_string_append (str, ", gpointer user_data)");
    else
        g_string_append (str, ")");

    anjuta_util_glist_strings_free (names);

    return str;
}
