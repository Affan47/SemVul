filter_revert_changes(void)
{
    GList *iter;

    if (GUI_PROPERTY(gui_debug) >= 5)
        g_debug("Canceling all changes to filters/rules");

    filter_gui_freeze_filters();
    filter_gui_freeze_rules();


    for (iter = shadow_filters; iter != NULL; iter = shadow_filters)
        shadow_cancel(iter->data);

    if (g_list_find(filters, work_filter) != NULL)
        filter_set(work_filter);
    else
        filter_set(NULL);

    g_list_free(filters_current);
    filters_current = g_list_copy(filters);


    for (iter = filters_added; iter != NULL; iter = filters_added) {
        filter_t *filter = iter->data;

        filter_gui_filter_remove(filter);
        filter_free(filter);
    }
    g_assert(filters_added == NULL);


    for (iter = filters_removed; iter != NULL; iter = g_list_next(iter)) {
        filter_t *filter = iter->data;

        filter_gui_filter_add(filter, filter->ruleset);
    }
    gm_list_free_null(&filters_removed);


    for (iter = filters_current; iter != NULL; iter = g_list_next(iter)) {
        filter_t *filter = iter->data;

        filter_gui_update_rule_count(filter, filter->ruleset);
        filter_gui_filter_set_enabled(filter, filter_is_active(filter));
    }

    filter_gui_thaw_rules();
    filter_gui_thaw_filters();

    filter_update_targets();
}
