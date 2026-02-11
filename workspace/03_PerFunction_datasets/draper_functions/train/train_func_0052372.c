group_update_pseudo_status(resource_t * parent, resource_t * child)
{
    GListPtr gIter = child->actions;
    group_variant_data_t *group_data = NULL;

    get_group_variant_data(group_data, parent);

    if (group_data->ordered == FALSE) {

        return;
    }

    if (group_data->child_stopping && group_data->child_starting) {
        return;
    }

    for (; gIter != NULL; gIter = gIter->next) {
        action_t *action = (action_t *) gIter->data;

        if (is_set(action->flags, pe_action_optional)) {
            continue;
        }
        if (safe_str_eq(RSC_STOP, action->task) && is_set(action->flags, pe_action_runnable)) {
            group_data->child_stopping = TRUE;
            pe_rsc_trace(action->rsc, "Based on %s the group is stopping", action->uuid);

        } else if (safe_str_eq(RSC_START, action->task)
                   && is_set(action->flags, pe_action_runnable)) {
            group_data->child_starting = TRUE;
            pe_rsc_trace(action->rsc, "Based on %s the group is starting", action->uuid);
        }
    }
}
