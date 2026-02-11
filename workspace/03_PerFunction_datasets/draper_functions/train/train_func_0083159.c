ns_from_locpath(struct locpath *lp, uint *maxns,
                            struct nodeset ***ns,
                            const struct nodeset *root,
                            struct state *state) {
    struct tree *old_ctx = state->ctx;

    *maxns = 0;
    *ns = NULL;
    list_for_each(step, lp->steps)
        *maxns += 1;
    if (ALLOC_N(*ns, *maxns+1) < 0) {
        STATE_ERROR(state, PATHX_ENOMEM);
        goto error;
    }
    for (int i=0; i <= *maxns; i++) {
        (*ns)[i] = make_nodeset(state);
        if (HAS_ERROR(state))
            goto error;
    }

    if (root == NULL) {
        struct step *first_step = NULL;
        if (lp != NULL)
            first_step = lp->steps;

        struct tree *root_tree;
        root_tree = step_root(first_step, state->ctx, state->root_ctx);
        ns_add((*ns)[0], root_tree, state);
    } else {
        for (int i=0; i < root->used; i++)
            ns_add((*ns)[0], root->nodes[i], state);
    }

    if (HAS_ERROR(state))
        goto error;

    uint cur_ns = 0;
    list_for_each(step, lp->steps) {
        struct nodeset *work = (*ns)[cur_ns];
        struct nodeset *next = (*ns)[cur_ns + 1];
        for (int i=0; i < work->used; i++) {
            for (struct tree *node = step_first(step, work->nodes[i]);
                 node != NULL;
                 node = step_next(step, work->nodes[i], node))
                ns_add(next, node, state);
        }
        ns_filter(next, step->predicates, state);
        if (HAS_ERROR(state))
            goto error;
        cur_ns += 1;
    }

    state->ctx = old_ctx;
    return;
 error:
    if (*ns != NULL) {
        for (int i=0; i <= *maxns; i++)
            free_nodeset((*ns)[i]);
        FREE(*ns);
    }
    state->ctx = old_ctx;
    return;
}
