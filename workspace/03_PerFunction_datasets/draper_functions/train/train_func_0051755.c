lad_sm_change_array_inner(Module_table *module,
			  StripMining *sm,
			  Var_table *offset,
			  Array_table *ldm,
			  int dim)
{
    List *li;
    StripMiningInnerLoop *smil;
    Block *block;

    for (li = sm->loops; li != NULL; li = li->next) {
	smil = SMIL(li->data);
	block = smil->block;
	lad_sm_change_array_inner_block(block, offset, ldm, dim, smil);
    }
}
