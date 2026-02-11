check_usemap_section_nr(int nid, unsigned long *usemap)
{
	unsigned long usemap_snr, pgdat_snr;
	static unsigned long old_usemap_snr = NR_MEM_SECTIONS;
	static unsigned long old_pgdat_snr = NR_MEM_SECTIONS;
	struct pglist_data *pgdat = NODE_DATA(nid);
	int usemap_nid;

	usemap_snr = pfn_to_section_nr(__pa(usemap) >> PAGE_SHIFT);
	pgdat_snr = pfn_to_section_nr(__pa(pgdat) >> PAGE_SHIFT);
	if (usemap_snr == pgdat_snr)
		return;

	if (old_usemap_snr == usemap_snr && old_pgdat_snr == pgdat_snr)

		return;

	old_usemap_snr = usemap_snr;
	old_pgdat_snr = pgdat_snr;

	usemap_nid = sparse_early_nid(__nr_to_section(usemap_snr));
	if (usemap_nid != nid) {
		printk(KERN_INFO
		       "node %d must be removed before remove section %ld\n",
		       nid, usemap_snr);
		return;
	}


	printk(KERN_INFO "Section %ld and %ld (node %d)", usemap_snr,
	       pgdat_snr, nid);
	printk(KERN_CONT
	       " have a circular dependency on usemap and pgdat allocations\n");
}
