order_actions(action_t * lh_action, action_t * rh_action, enum pe_ordering order)
{
    GListPtr gIter = NULL;
    action_wrapper_t *wrapper = NULL;
    GListPtr list = NULL;

    if (order == pe_order_none) {
        return FALSE;
    }

    if (lh_action == NULL || rh_action == NULL) {
        return FALSE;
    }

    crm_trace("Ordering Action %s before %s", lh_action->uuid, rh_action->uuid);


    gIter = lh_action->actions_after;
    for (; gIter != NULL; gIter = gIter->next) {
        action_wrapper_t *after = (action_wrapper_t *) gIter->data;

        if (after->action == rh_action && (after->type & order)) {
            return FALSE;
        }
    }

    wrapper = calloc(1, sizeof(action_wrapper_t));
    wrapper->action = rh_action;
    wrapper->type = order;

    list = lh_action->actions_after;
    list = g_list_prepend(list, wrapper);
    lh_action->actions_after = list;

    wrapper = NULL;


    wrapper = calloc(1, sizeof(action_wrapper_t));
    wrapper->action = lh_action;
    wrapper->type = order;
    list = rh_action->actions_before;
    list = g_list_prepend(list, wrapper);
    rh_action->actions_before = list;
    return TRUE;
}
