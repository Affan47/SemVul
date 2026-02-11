create_listeners (void)
{
    GList *listeners = NULL, *node;

    for (node = factories; node; node = g_list_next(node)) {
        GObject *listener;
        listener = cut_module_factory_create(CUT_MODULE_FACTORY(node->data));
        listeners = g_list_prepend(listeners, listener);
    }

    return listeners;
}
