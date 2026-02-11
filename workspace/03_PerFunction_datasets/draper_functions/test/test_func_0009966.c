bcma_core_chipcommon_b_init(struct bcma_drv_cc_b *ccb)
{
	if (ccb->setup_done)
		return 0;

	ccb->setup_done = 1;
	ccb->mii = ioremap_nocache(ccb->core->addr_s[1], BCMA_CORE_SIZE);
	if (!ccb->mii)
		return -ENOMEM;

	return 0;
}
