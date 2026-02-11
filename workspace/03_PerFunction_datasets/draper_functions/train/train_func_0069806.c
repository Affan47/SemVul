add_pe_stm_of_BB(Block *bpt, int vpe_cnt)
{
    Block *b = bpt;

    if (bpt->inner != NULL)
	add_pe_stm_of_BB_inner(b, vpe_cnt);

    set_add_pe_stm_of_BB(b, vpe_cnt);

    return b;
}
