stage3(pe_working_set_t * data_set)
{

    GListPtr gIter = data_set->resources;

    for (; gIter != NULL; gIter = gIter->next) {
        resource_t *rsc = (resource_t *) gIter->data;

        rsc->cmds->internal_constraints(rsc, data_set);
    }

    return TRUE;
}
