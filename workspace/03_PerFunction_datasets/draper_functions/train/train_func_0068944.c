set_option_context (CutFactoryBuilder *builder, GOptionContext *context)
{
    static gchar *arg_description = NULL;
    GOptionGroup *group;
    GOptionEntry entries[] = {
        {"ui", 'u', 0, G_OPTION_ARG_STRING, &ui_name,
         N_("Specify UI"), NULL},
        {NULL}
    };

    if (!arg_description) {
        GString *available_uis;
        GList *names, *node;

        available_uis = g_string_new("[");
        names = cut_module_factory_get_names("ui");
        for (node = names; node; node = g_list_next(node)) {
            const gchar *name = node->data;
            g_string_append(available_uis, name);
            if (g_list_next(node))
                g_string_append(available_uis, "|");
        }
        g_string_append(available_uis, "]");
        arg_description = g_string_free(available_uis, FALSE);

        g_list_foreach(names, (GFunc)g_free, NULL);
        g_list_free(names);
    }
    entries[0].arg_description = arg_description;

    group = g_option_group_new(("ui"),
                               _("UI Options"),
                               _("Show UI options"),
                               builder, NULL);
    g_option_group_add_entries(group, entries);
    g_option_group_set_translation_domain(group, GETTEXT_PACKAGE);
    g_option_context_add_group(context, group);
}
