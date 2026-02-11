add_listeners (CutRunContext *run_context, GList *listeners)
{
    GList *node;

    for (node = listeners; node; node = g_list_next(node)) {
        CutListener *listener = CUT_LISTENER(node->data);
        cut_run_context_add_listener(run_context, listener);
    }
}
