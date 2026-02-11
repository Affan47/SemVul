find_best_apply_object_match(object *start, object *pl, const char *params, int aflag) {
    object *tmp, *best = NULL;
    int match_val = 0, tmpmatch;

    tmp = start;
    FOR_OB_AND_BELOW_PREPARE(tmp) {
        if (tmp->invisible)
            continue;
        if (aflag == AP_APPLY && QUERY_FLAG(tmp, FLAG_APPLIED))
            continue;
        if (aflag == AP_UNAPPLY && !QUERY_FLAG(tmp, FLAG_APPLIED))
            continue;
        tmpmatch = object_matches_string(pl, tmp, params);
        if (tmpmatch > match_val) {
            match_val = tmpmatch;
            best = tmp;
        }
    } FOR_OB_AND_BELOW_FINISH();
    return best;
}
