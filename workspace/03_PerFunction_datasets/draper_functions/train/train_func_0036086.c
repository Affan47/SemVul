gather_used_var(Block *block, IntSet local_var)
{
    Pe_statement *pestm;

    for (pestm = block->pre_head; pestm != NULL; pestm = pestm->next) {
	local_var = gather_used_var_in_pe_statement(pestm, local_var);
    }

    if (block->inner != NULL) {
	local_var = gather_used_var_in_block(block->inner, local_var);
    }

    for (pestm = block->post_head; pestm != NULL; pestm = pestm->next) {
	local_var = gather_used_var_in_pe_statement(pestm, local_var);
    }

    return local_var;
}
