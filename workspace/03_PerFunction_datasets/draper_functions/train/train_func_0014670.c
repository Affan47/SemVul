use_shifted(struct isl_context_gbr *cgbr)
{
	return cgbr->tab->bmap->n_eq == 0 && cgbr->tab->bmap->n_div == 0;
}
