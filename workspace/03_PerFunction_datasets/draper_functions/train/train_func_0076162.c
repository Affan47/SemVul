clone_update_pseudo_status(resource_t * rsc, gboolean * stopping, gboolean * starting,
                           gboolean * active)
{
    GListPtr gIter = NULL;

    if (rsc->children) {

        gIter = rsc->children;
        for (; gIter != NULL; gIter = gIter->next) {
            resource_t *child = (resource_t *) gIter->data;

            clone_update_pseudo_status(child, stopping, starting, active);
        }

        return;
    }

    CRM_ASSERT(active != NULL);
    CRM_ASSERT(starting != NULL);
    CRM_ASSERT(stopping != NULL);

    if (rsc->running_on) {
        *active = TRUE;
    }

    gIter = rsc->actions;
    for (; gIter != NULL; gIter = gIter->next) {
        action_t *action = (action_t *) gIter->data;

        if (*starting && *stopping) {
            return;

        } else if (is_set(action->flags, pe_action_optional)) {
            pe_rsc_trace(rsc, "Skipping optional: %s", action->uuid);
            continue;

        } else if (is_set(action->flags, pe_action_pseudo) == FALSE
                   && is_set(action->flags, pe_action_runnable) == FALSE) {
            pe_rsc_trace(rsc, "Skipping unrunnable: %s", action->uuid);
            continue;

        } else if (safe_str_eq(RSC_STOP, action->task)) {
            pe_rsc_trace(rsc, "Stopping due to: %s", action->uuid);
            *stopping = TRUE;

        } else if (safe_str_eq(RSC_START, action->task)) {
            if (is_set(action->flags, pe_action_runnable) == FALSE) {
                pe_rsc_trace(rsc, "Skipping pseudo-op: %s run=%d, pseudo=%d",
                             action->uuid, is_set(action->flags, pe_action_runnable),
                             is_set(action->flags, pe_action_pseudo));
            } else {
                pe_rsc_trace(rsc, "Starting due to: %s", action->uuid);
                pe_rsc_trace(rsc, "%s run=%d, pseudo=%d",
                             action->uuid, is_set(action->flags, pe_action_runnable),
                             is_set(action->flags, pe_action_pseudo));
                *starting = TRUE;
            }
        }
    }
}
