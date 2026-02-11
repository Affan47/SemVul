parse_step(struct state *state) {
    struct step *step;
    int explicit_axis = 0, allow_predicates = 1;

    if (ALLOC(step) < 0) {
        STATE_ENOMEM;
        return NULL;
    }

    step->axis = CHILD;
    for (int i = 0; i < ARRAY_CARDINALITY(axis_names); i++) {
        if (looking_at(state, axis_names[i], "::")) {
            step->axis = i;
            explicit_axis = 1;
            break;
        }
    }

    if (! match(state, '*')) {
        step->name = parse_name(state);
        if (HAS_ERROR(state))
            goto error;
        if (! explicit_axis) {
            if (STREQ(step->name, ".") || STREQ(step->name, "..")) {
                step->axis = STREQ(step->name, ".") ? SELF : PARENT;
                FREE(step->name);
                allow_predicates = 0;
            }
        }
    }

    if (allow_predicates) {
        step->predicates = parse_predicates(state);
        if (HAS_ERROR(state))
            goto error;
    }

    return step;

 error:
    free_step(step);
    return NULL;
}
