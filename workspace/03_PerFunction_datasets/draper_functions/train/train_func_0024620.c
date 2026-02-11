bfa_nw_ioc_smem_read(struct bfa_ioc *ioc, void *tbuf, u32 soff, u32 sz)
{
	u32 pgnum, loff, r32;
	int i, len;
	u32 *buf = tbuf;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, soff);
	loff = PSS_SMEM_PGOFF(soff);


	if (!bfa_nw_ioc_sem_get(ioc->ioc_regs.ioc_init_sem_reg))
		return 1;

	writel(pgnum, ioc->ioc_regs.host_page_num_fn);

	len = sz/sizeof(u32);
	for (i = 0; i < len; i++) {
		r32 = swab32(readl(loff + ioc->ioc_regs.smem_page_start));
		buf[i] = be32_to_cpu(r32);
		loff += sizeof(u32);


		loff = PSS_SMEM_PGOFF(loff);
		if (loff == 0) {
			pgnum++;
			writel(pgnum, ioc->ioc_regs.host_page_num_fn);
		}
	}

	writel(PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, 0),
	       ioc->ioc_regs.host_page_num_fn);


	readl(ioc->ioc_regs.ioc_init_sem_reg);
	writel(1, ioc->ioc_regs.ioc_init_sem_reg);
	return 0;
}
