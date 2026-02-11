sm_read_regs(struct fpi_ssm *ssm, uint16_t reg, uint16_t num_regs)
{
	struct fp_img_dev *dev = ssm->priv;
	struct uru4k_dev *urudev = dev->priv;
	int r;

	if (num_regs > sizeof(urudev->last_reg_rd)) {
		fpi_ssm_mark_aborted(ssm, -EIO);
		return;
	}

	fp_dbg("read %d regs at %x", num_regs, reg);
	r = read_regs(dev, reg, num_regs, sm_read_reg_cb, ssm);
	if (r < 0)
		fpi_ssm_mark_aborted(ssm, r);
}
