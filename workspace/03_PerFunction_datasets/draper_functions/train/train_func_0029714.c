aty128_decode_var(struct fb_var_screeninfo *var,
			     struct aty128fb_par *par)
{
	int err;
	struct aty128_crtc crtc;
	struct aty128_pll pll;
	struct aty128_ddafifo fifo_reg;

	if ((err = aty128_var_to_crtc(var, &crtc, par)))
		return err;

	if ((err = aty128_var_to_pll(var->pixclock, &pll, par)))
		return err;

	if ((err = aty128_ddafifo(&fifo_reg, &pll, crtc.depth, par)))
		return err;

	par->crtc = crtc;
	par->pll = pll;
	par->fifo_reg = fifo_reg;
	par->accel_flags = var->accel_flags;

	return 0;
}
