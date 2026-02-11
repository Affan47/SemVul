ah_parse(struct xt_option_call *cb)
{
	struct ip6t_ah *ahinfo = cb->data;

	xtables_option_parse(cb);
	switch (cb->entry->id) {
	case O_AHSPI:
		if (cb->nvals == 1)
			ahinfo->spis[1] = ahinfo->spis[0];
		if (cb->invert)
			ahinfo->invflags |= IP6T_AH_INV_SPI;
		break;
	case O_AHLEN:
		if (cb->invert)
			ahinfo->invflags |= IP6T_AH_INV_LEN;
		break;
	case O_AHRES:
		ahinfo->hdrres = 1;
		break;
	}
}
