make_sb_rd(Block *bp, RdState *rs)
{
    Module_table *callee;

    reset_RdState(rs);

    callee = search_callee_module(bp);
    rs->reach_def = copy_rd_list(callee->block_head->tail_rd);

    if (lang_tag == LANG_FORTRAN)
	get_arg_reach_def(bp, callee, rs);
    get_global_reach_def(bp, rs);

    make_block_reach_def(callee->block_head, rs);

    replace_arg_and_global_rd(rs, bp, callee);
}
