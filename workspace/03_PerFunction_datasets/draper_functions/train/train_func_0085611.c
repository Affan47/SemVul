gather_used_var_in_block(Block *block, IntSet local_var)
{
    Block *bpt;
    for (bpt = block; bpt != NULL; bpt = bpt->next) {
	local_var = gather_used_var(bpt, local_var);
    }
    return local_var;
}
