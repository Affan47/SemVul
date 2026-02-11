set_option_group (CutModuleFactory *factory, GOptionContext *context)
{
    GOptionGroup *group;

    if (CUT_MODULE_FACTORY_CLASS(parent_class)->set_option_group)
        CUT_MODULE_FACTORY_CLASS(parent_class)->set_option_group(factory, context);

    group = gtk_get_option_group(TRUE);
    g_option_context_add_group(context, group);
}
