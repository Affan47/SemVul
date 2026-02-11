syn_clear_one(id, syncing)
    int		id;
    int		syncing;
{
    synpat_T	*spp;
    int		idx;


    if (!syncing)
    {
	(void)syn_clear_keyword(id, &curbuf->b_keywtab);
	(void)syn_clear_keyword(id, &curbuf->b_keywtab_ic);
    }


    for (idx = curbuf->b_syn_patterns.ga_len; --idx >= 0; )
    {
	spp = &(SYN_ITEMS(curbuf)[idx]);
	if (spp->sp_syn.id != id || spp->sp_syncing != syncing)
	    continue;
	syn_remove_pattern(curbuf, idx);
    }
}
