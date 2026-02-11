rss_pf_config_show(struct seq_file *seq, void *v, int idx)
{
	struct rss_pf_conf *pfconf;

	if (v == SEQ_START_TOKEN) {

		pfconf = seq->private + offsetof(struct seq_tab, data);
		seq_printf(seq, "PF Map Index Size = %d\n\n",
			   LKPIDXSIZE_G(pfconf->rss_pf_map));

		seq_puts(seq, "     RSS              PF   VF    Hash Tuple Enable         Default\n");
		seq_puts(seq, "     Enable       IPF Mask Mask  IPv6      IPv4      UDP   Queue\n");
		seq_puts(seq, " PF  Map Chn Prt  Map Size Size  Four Two  Four Two  Four  Ch1  Ch0\n");
	} else {
		#define G_PFnLKPIDX(map, n) \
			(((map) >> PF1LKPIDX_S*(n)) & PF0LKPIDX_M)
		#define G_PFnMSKSIZE(mask, n) \
			(((mask) >> PF1MSKSIZE_S*(n)) & PF1MSKSIZE_M)

		pfconf = v;
		seq_printf(seq, "%3d  %3s %3s %3s  %3d  %3d  %3d   %3s %3s   %3s %3s   %3s  %3d  %3d\n",
			   idx,
			   yesno(pfconf->rss_pf_config & MAPENABLE_F),
			   yesno(pfconf->rss_pf_config & CHNENABLE_F),
			   yesno(pfconf->rss_pf_config & PRTENABLE_F),
			   G_PFnLKPIDX(pfconf->rss_pf_map, idx),
			   G_PFnMSKSIZE(pfconf->rss_pf_mask, idx),
			   IVFWIDTH_G(pfconf->rss_pf_config),
			   yesno(pfconf->rss_pf_config & IP6FOURTUPEN_F),
			   yesno(pfconf->rss_pf_config & IP6TWOTUPEN_F),
			   yesno(pfconf->rss_pf_config & IP4FOURTUPEN_F),
			   yesno(pfconf->rss_pf_config & IP4TWOTUPEN_F),
			   yesno(pfconf->rss_pf_config & UDPFOURTUPEN_F),
			   CH1DEFAULTQUEUE_G(pfconf->rss_pf_config),
			   CH0DEFAULTQUEUE_G(pfconf->rss_pf_config));

		#undef G_PFnLKPIDX
		#undef G_PFnMSKSIZE
	}
	return 0;
}
