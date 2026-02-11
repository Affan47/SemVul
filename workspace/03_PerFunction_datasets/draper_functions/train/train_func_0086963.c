make_loop_rd(Block *loop, RdState *rs)
{
    rs->change = FALSE;
    if (loop->pre_head != NULL)
	make_statement_rd(loop->pre_head->stm_head, rs);
    loop->head_rd = or_rd_list(rs, loop->head_rd, rs->reach_def);
    loop->head_rd = or_rd_list(rs, loop->head_rd, loop->tail_rd);
    while (rs->change) {
	reset_RdState(rs);
	rs->reach_def = copy_rd_list(loop->head_rd);
	make_block_reach_def(loop->inner, rs);
	rs->change = FALSE;
	loop->head_rd = or_rd_list(rs, loop->head_rd, rs->reach_def);
    }
}
