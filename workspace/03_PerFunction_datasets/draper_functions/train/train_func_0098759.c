tlg_has_same_edcond(const Tlg *tlg) {
    Boolean flg_edcond;
    IntSet  (*edcond);
    int mt_num;
    int i;

    mt_num = get_number_of_inner_blocks(tlg->block);
    edcond = malloc((mt_num + 1) *sizeof(IntSet));
    if (edcond == NULL)
        fatal("alloc failed\n");
    make_exec_determinating_cond(tlg->block, edcond);

    flg_edcond = TRUE;
    for (i = min_IntSet(tlg->mt_set); i <= max_IntSet(tlg->mt_set); i++) {
        if (in_IntSet(tlg->mt_set, i)) {
            if (!equal_IntSet(edcond[i-1], edcond[tlg->std->no-1])) {
                flg_edcond = FALSE;
                break;
            }
        }
    }

    for (i = 0; i < mt_num + 1; i++) {
        destruct_IntSet(edcond[i]);
    }
    free(edcond);

    return flg_edcond;
}
