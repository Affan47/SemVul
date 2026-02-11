print_stats_dev_struct(const struct stats_dev *p,
		const struct stats_dev *c, cputime_t itv)
{
	int unit = 1;

	if (option_mask32 & OPT_k)
		unit = 2;
	else if (option_mask32 & OPT_m)
		unit = 2048;

	if (option_mask32 & OPT_z)
		if (p->rd_ops == c->rd_ops && p->wr_ops == c->wr_ops)
			return;

	printf("%-13s", c->dname);
	printf(" %8.2f %12.2f %12.2f %10llu %10llu \n",
		percent_value(p->rd_ops + p->wr_ops ,
				  c->rd_ops + c->wr_ops , itv),
		percent_value(p->rd_sectors, c->rd_sectors, itv) / unit,
		percent_value(p->wr_sectors, c->wr_sectors, itv) / unit,
		(c->rd_sectors - p->rd_sectors) / unit,
		(c->wr_sectors - p->wr_sectors) / unit);
}
