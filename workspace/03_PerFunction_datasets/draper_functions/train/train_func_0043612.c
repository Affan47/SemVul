add_mon_to_reg(reg, mon)
NhRegion *reg;
struct monst *mon;
{
    int i;
    unsigned *tmp_m;

    if (reg->max_monst <= reg->n_monst) {
	tmp_m = (unsigned *)
		    alloc(sizeof (unsigned) * (reg->max_monst + MONST_INC));
	if (reg->max_monst > 0) {
	    for (i = 0; i < reg->max_monst; i++)
		tmp_m[i] = reg->monsters[i];
	    free((genericptr_t) reg->monsters);
	}
	reg->monsters = tmp_m;
	reg->max_monst += MONST_INC;
    }
    reg->monsters[reg->n_monst++] = mon->m_id;
}
