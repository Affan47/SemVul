bfa_ioc_fwver_get(struct bfa_ioc_s *ioc, struct bfi_ioc_image_hdr_s *fwhdr)
{
	u32	pgnum, pgoff;
	u32	loff = 0;
	int		i;
	u32	*fwsig = (u32 *) fwhdr;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, loff);
	pgoff = PSS_SMEM_PGOFF(loff);
	writel(pgnum, ioc->ioc_regs.host_page_num_fn);

	for (i = 0; i < (sizeof(struct bfi_ioc_image_hdr_s) / sizeof(u32));
	     i++) {
		fwsig[i] =
			bfa_mem_read(ioc->ioc_regs.smem_page_start, loff);
		loff += sizeof(u32);
	}
}
