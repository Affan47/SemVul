render_paging_stats(struct activity *a, int isdb, char *pre,
				    int curr, unsigned long long itv)
{
	struct stats_paging
		*spc = (struct stats_paging *) a->buf[curr],
		*spp = (struct stats_paging *) a->buf[!curr];
	int pt_newlin
		= (DISPLAY_HORIZONTALLY(flags) ? PT_NOFLAG : PT_NEWLIN);

	render(isdb, pre, PT_NOFLAG,
	       "-\tpgpgin/s", NULL, NULL,
	       NOVAL,
	       S_VALUE(spp->pgpgin, spc->pgpgin, itv),
	       NULL);

	render(isdb, pre, PT_NOFLAG,
	       "-\tpgpgout/s", NULL, NULL,
	       NOVAL,
	       S_VALUE(spp->pgpgout, spc->pgpgout, itv),
	       NULL);

	render(isdb, pre, PT_NOFLAG,
	       "-\tfault/s", NULL, NULL,
	       NOVAL,
	       S_VALUE(spp->pgfault, spc->pgfault, itv),
	       NULL);

	render(isdb, pre, PT_NOFLAG,
	       "-\tmajflt/s", NULL, NULL,
	       NOVAL,
	       S_VALUE(spp->pgmajfault, spc->pgmajfault, itv),
	       NULL);

	render(isdb, pre, PT_NOFLAG,
	       "-\tpgfree/s", NULL, NULL,
	       NOVAL,
	       S_VALUE(spp->pgfree, spc->pgfree, itv),
	       NULL);

	render(isdb, pre, PT_NOFLAG,
	       "-\tpgscank/s", NULL, NULL,
	       NOVAL,
	       S_VALUE(spp->pgscan_kswapd, spc->pgscan_kswapd, itv),
	       NULL);

	render(isdb, pre, PT_NOFLAG,
	       "-\tpgscand/s", NULL, NULL,
	       NOVAL,
	       S_VALUE(spp->pgscan_direct, spc->pgscan_direct, itv),
	       NULL);

	render(isdb, pre, PT_NOFLAG,
	       "-\tpgsteal/s", NULL, NULL,
	       NOVAL,
	       S_VALUE(spp->pgsteal, spc->pgsteal, itv),
	       NULL);

	render(isdb, pre, pt_newlin,
	       "-\t%%vmeff", NULL, NULL,
	       NOVAL,
	       (spc->pgscan_kswapd + spc->pgscan_direct -
		spp->pgscan_kswapd - spp->pgscan_direct) ?
	       SP_VALUE(spp->pgsteal, spc->pgsteal,
			spc->pgscan_kswapd + spc->pgscan_direct -
			spp->pgscan_kswapd - spp->pgscan_direct) : 0.0,
	       NULL);
}
