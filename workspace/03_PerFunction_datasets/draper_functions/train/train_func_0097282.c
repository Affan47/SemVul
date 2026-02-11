sx_recurrence_handler(xmlNodePtr node, gpointer _pdata)
{
    struct sx_pdata *parsing_data = _pdata;
    GList *schedule = NULL;
    gchar* debug_str;

    g_return_val_if_fail(node, FALSE);

    if (!dom_tree_generic_parse(node, sx_recurrence_list_handlers, &schedule))
        return FALSE;

    debug_str = recurrenceListToString(schedule);
    g_debug("setting freshly-parsed schedule: [%s]", debug_str);
    g_free(debug_str);
    gnc_sx_set_schedule(parsing_data->sx, schedule);
    parsing_data->saw_recurrence = TRUE;
    return TRUE;
}
