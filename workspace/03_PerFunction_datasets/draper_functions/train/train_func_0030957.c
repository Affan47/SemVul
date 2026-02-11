bfa_ioc_hw_sem_init(struct bfa_ioc *ioc)
{
	struct bfi_ioc_image_hdr fwhdr;
	u32 fwstate, r32;


	r32 = readl(ioc->ioc_regs.ioc_init_sem_reg);
	while (r32 & 0x1) {
		udelay(20);
		r32 = readl(ioc->ioc_regs.ioc_init_sem_reg);
	}

	fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);
	if (fwstate == BFI_IOC_UNINIT) {
		writel(1, ioc->ioc_regs.ioc_init_sem_reg);
		return;
	}

	bfa_nw_ioc_fwver_get(ioc, &fwhdr);

	if (swab32(fwhdr.exec) == BFI_FWBOOT_TYPE_NORMAL) {
		writel(1, ioc->ioc_regs.ioc_init_sem_reg);
		return;
	}

	bfa_ioc_fwver_clear(ioc);
	bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_UNINIT);
	bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_UNINIT);


	readl(ioc->ioc_regs.ioc_sem_reg);
	writel(1, ioc->ioc_regs.ioc_sem_reg);


	writel(1, ioc->ioc_regs.ioc_init_sem_reg);
}
