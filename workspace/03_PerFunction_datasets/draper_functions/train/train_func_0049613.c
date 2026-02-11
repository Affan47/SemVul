build_all (CutFactoryBuilder *builder)
{
    GList *factories = NULL, *node;
    GList *factory_names;

    factory_names = cut_module_factory_get_names("ui");

    for (node = factory_names; node; node = g_list_next(node)) {
        CutModuleFactory *module_factory;
        GOptionContext *option_context;
        module_factory = cut_module_factory_new("ui", node->data, NULL);
        g_object_get(builder,
                     "option-context", &option_context,
                     NULL);
        cut_module_factory_set_option_group(module_factory,
                                            option_context);
        factories = g_list_prepend(factories, module_factory);
    }

    return g_list_reverse(factories);
}
