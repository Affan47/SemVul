xml_print_paging_stats(struct activity *a, int curr, int tab,
				       unsigned long long itv)
{
	struct stats_paging
		*spc = (struct stats_paging *) a->buf[curr],
		*spp = (struct stats_paging *) a->buf[!curr];

	xprintf(tab, "<paging per=\"second\" "
		"pgpgin=\"%.2f\" "
		"pgpgout=\"%.2f\" "
		"fault=\"%.2f\" "
		"majflt=\"%.2f\" "
		"pgfree=\"%.2f\" "
		"pgscank=\"%.2f\" "
		"pgscand=\"%.2f\" "
		"pgsteal=\"%.2f\" "
		"vmeff-percent=\"%.2f\"/>",
		S_VALUE(spp->pgpgin,        spc->pgpgin,        itv),
		S_VALUE(spp->pgpgout,       spc->pgpgout,       itv),
		S_VALUE(spp->pgfault,       spc->pgfault,       itv),
		S_VALUE(spp->pgmajfault,    spc->pgmajfault,    itv),
		S_VALUE(spp->pgfree,        spc->pgfree,        itv),
		S_VALUE(spp->pgscan_kswapd, spc->pgscan_kswapd, itv),
		S_VALUE(spp->pgscan_direct, spc->pgscan_direct, itv),
		S_VALUE(spp->pgsteal,       spc->pgsteal,       itv),
		(spc->pgscan_kswapd + spc->pgscan_direct -
		 spp->pgscan_kswapd - spp->pgscan_direct) ?
		SP_VALUE(spp->pgsteal, spc->pgsteal,
			 spc->pgscan_kswapd + spc->pgscan_direct -
			 spp->pgscan_kswapd - spp->pgscan_direct) : 0.0);
}
