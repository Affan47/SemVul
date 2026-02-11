ctl_page_to_phys(struct mem_ctl_info *mci,
				unsigned long page)
{
	u32 remap;
	struct e752x_pvt *pvt = (struct e752x_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	if (page < pvt->tolm)
		return page;

	if ((page >= 0x100000) && (page < pvt->remapbase))
		return page;

	remap = (page - pvt->tolm) + pvt->remapbase;

	if (remap < pvt->remaplimit)
		return remap;

	e752x_printk(KERN_ERR, "Invalid page %lx - out of range\n", page);
	return pvt->tolm - 1;
}
