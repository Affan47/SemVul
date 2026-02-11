has_common_range(SymRange *rng0, SymRange *rng1)
{
    SemTree *lower0, *lower1;
    SemTree *upper0, *upper1;

    Boolean ret = TRUE;

    if (rng0->l == NULL
        || rng0->u == NULL
        || rng1->l == NULL
        || rng1->u == NULL)
        return TRUE;

    lower0 = semtree_dup(rng0->l);
    lower1 = semtree_dup(rng1->l);
    upper0 = semtree_dup(rng0->u);
    upper1 = semtree_dup(rng1->u);

    if (compare_semtree(lower0, lower1) == -1
        && compare_semtree(upper0, lower1) == -1) {
        ret = FALSE;
    }

    if (compare_semtree(lower1, lower0) == -1
        && compare_semtree(upper1, lower0) == -1) {
        ret = FALSE;
    }

    if (!semtree_is_const(lower0) && semtree_is_const(upper0)) {
        if (compare_semtree(upper0, lower0) != SYM_ERR)
            return FALSE;
    }

    if (!semtree_is_const(lower1) && semtree_is_const(upper1)) {
        if (compare_semtree(upper1, lower1) != SYM_ERR)
            return FALSE;
    }

    semtree_destruct(lower0);
    semtree_destruct(lower1);
    semtree_destruct(upper0);
    semtree_destruct(upper1);

    return ret;
}
