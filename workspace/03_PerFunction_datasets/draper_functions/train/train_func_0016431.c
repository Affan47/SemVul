ov965x_update_exposure_ctrl(struct ov965x *ov965x)
{
	struct v4l2_ctrl *ctrl = ov965x->ctrls.exposure;
	unsigned long fint, trow;
	int min, max, def;
	u8 clkrc;

	mutex_lock(&ov965x->lock);
	if (WARN_ON(!ctrl || !ov965x->frame_size)) {
		mutex_unlock(&ov965x->lock);
		return;
	}
	clkrc = DEF_CLKRC + ov965x->fiv->clkrc_div;

	fint = ov965x->mclk_frequency * ((clkrc >> 7) + 1) /
				((2 * ((clkrc & 0x3f) + 1)));

	trow = (2 * 1520 * 1000000UL) / fint;
	max = ov965x->frame_size->max_exp_lines * trow;
	ov965x->exp_row_interval = trow;
	mutex_unlock(&ov965x->lock);

	v4l2_dbg(1, debug, &ov965x->sd, "clkrc: %#x, fi: %lu, tr: %lu, %d\n",
		 clkrc, fint, trow, max);


	min = (trow + 100) / 100;
	max = (max - 100) / 100;
	def = min + (max - min) / 2;

	if (v4l2_ctrl_modify_range(ctrl, min, max, 1, def))
		v4l2_err(&ov965x->sd, "Exposure ctrl range update failed\n");
}
