shadow_cancel(shadow_t *shadow)
{
    GList *r;

    g_assert(shadow != NULL);
    g_assert(shadow->filter != NULL);

    if (GUI_PROPERTY(gui_debug) >= 6)
        g_debug("cancel shadow for filter: %s", shadow->filter->name);

    for (r = shadow->added; r != NULL; r = r->next)
        filter_free_rule(r->data);


    gm_list_free_null(&shadow->removed);
    gm_list_free_null(&shadow->added);
    gm_list_free_null(&shadow->current);

    shadow_filters = g_list_remove(shadow_filters, shadow);
    WFREE(shadow);
}
