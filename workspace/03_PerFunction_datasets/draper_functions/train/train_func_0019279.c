flush_strat_forward_fn(void *item, void *data)
{
    dico_strategy_t strat = item;
    dico_strategy_t p = dico_list_locate(strat_forward, strat->name);
    if (p && p->stratcl) {
	strat->stratcl = p->stratcl;
	p->stratcl = NULL;
    }
    return 0;
}
