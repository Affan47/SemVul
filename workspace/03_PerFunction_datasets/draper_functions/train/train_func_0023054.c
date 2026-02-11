rsc_migrate_reload(resource_t * rsc, pe_working_set_t * data_set)
{
    GListPtr gIter = NULL;
    action_t *stop = NULL;
    action_t *start = NULL;
    gboolean partial = FALSE;

    if(is_set(rsc->flags, pe_rsc_munging)) {
        return;
    }
    set_bit(rsc->flags, pe_rsc_munging);

    if (rsc->children) {
        for (gIter = rsc->children; gIter != NULL; gIter = gIter->next) {
            resource_t *child_rsc = (resource_t *) gIter->data;

            rsc_migrate_reload(child_rsc, data_set);
        }
        return;

    } else if (rsc->variant > pe_native) {
        return;
    }

    pe_rsc_trace(rsc, "Processing %s", rsc->id);

    if (rsc->partial_migration_target) {
        start = get_first_named_action(rsc, RSC_START, TRUE, rsc->partial_migration_target);
        stop = get_first_named_action(rsc, RSC_STOP, TRUE, rsc->partial_migration_source);
        if (start && stop) {
            partial = TRUE;
        }
    }

    pe_rsc_trace(rsc, "%s %s %p", rsc->id, partial ? "partial" : "full", stop);

    if (!partial) {
        stop =
            get_first_named_action(rsc, RSC_STOP, TRUE,
                                   rsc->running_on ? rsc->running_on->data : NULL);
        start = get_first_named_action(rsc, RSC_START, TRUE, NULL);
    }

    if (is_not_set(rsc->flags, pe_rsc_managed)
        || is_set(rsc->flags, pe_rsc_failed)
        || is_set(rsc->flags, pe_rsc_start_pending)
        || rsc->next_role < RSC_ROLE_STARTED || ((g_list_length(rsc->running_on) != 1) && !partial)) {
        pe_rsc_trace(rsc, "%s: general resource state: flags=0x%.16llx", rsc->id, rsc->flags);
        return;
    }

    if (stop != NULL && is_set(stop->flags, pe_action_optional) && is_set(rsc->flags, pe_rsc_try_reload)) {
        ReloadRsc(rsc, stop, start, data_set);

    } else if (stop == NULL || is_not_set(stop->flags, pe_action_optional)) {
        MigrateRsc(rsc, stop, start, data_set, partial);
    }
}
