block_contain_unknown_iter_loop(Block *block_head)
{
    Boolean contain_unknown_iter_loop = FALSE;
    Block *bpt;

    for (bpt = block_head; bpt; bpt = bpt->next) {
        Boolean fix_iter_p;

        if (bpt->inner != NULL)
            contain_unknown_iter_loop |= block_contain_unknown_iter_loop(bpt->inner);
        if (bpt->kind == SB)
            contain_unknown_iter_loop |= block_contain_unknown_iter_loop(search_callee_block_head(bpt));

        get_iteration(bpt, &fix_iter_p);
        contain_unknown_iter_loop |= !fix_iter_p;
    }
    return contain_unknown_iter_loop;
}
