camif_hw_set_lastirq(struct camif_vp *vp, int enable)
{
	u32 addr = S3C_CAMIF_REG_CICTRL(vp->id, vp->offset);
	u32 cfg;

	cfg = camif_read(vp->camif, addr);
	if (enable)
		cfg |= CICTRL_LASTIRQ_ENABLE;
	else
		cfg &= ~CICTRL_LASTIRQ_ENABLE;
	camif_write(vp->camif, addr, cfg);
}
