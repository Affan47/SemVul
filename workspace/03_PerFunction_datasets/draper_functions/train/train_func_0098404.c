PromoteRsc(resource_t * rsc, node_t * next, gboolean optional, pe_working_set_t * data_set)
{
    char *key = NULL;
    GListPtr gIter = NULL;
    gboolean runnable = TRUE;
    GListPtr action_list = NULL;

    pe_rsc_trace(rsc, "%s on %s", rsc->id, next ? next->details->uname : "N/A");

    CRM_CHECK(next != NULL, return FALSE);

    key = start_key(rsc);
    action_list = find_actions_exact(rsc->actions, key, next);
    free(key);

    for (gIter = action_list; gIter != NULL; gIter = gIter->next) {
        action_t *start = (action_t *) gIter->data;

        if (is_set(start->flags, pe_action_runnable) == FALSE) {
            runnable = FALSE;
        }
    }
    g_list_free(action_list);

    if (runnable) {
        promote_action(rsc, next, optional);
        return TRUE;
    }

    pe_rsc_debug(rsc, "%s\tPromote %s (canceled)", next->details->uname, rsc->id);

    key = promote_key(rsc);
    action_list = find_actions_exact(rsc->actions, key, next);
    free(key);

    for (gIter = action_list; gIter != NULL; gIter = gIter->next) {
        action_t *promote = (action_t *) gIter->data;

        update_action_flags(promote, pe_action_runnable | pe_action_clear);
    }

    g_list_free(action_list);
    return TRUE;
}
