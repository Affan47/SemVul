src_commit_write(struct hw *hw, unsigned int idx, void *blk)
{
	struct src_rsc_ctrl_blk *ctl = blk;
	int i;

	if (ctl->dirty.bf.czbfs) {

		for (i = 0; i < 8; i++)
			hw_write_20kx(hw, SRCUPZ+idx*0x100+i*0x4, 0);

		for (i = 0; i < 4; i++)
			hw_write_20kx(hw, SRCDN0Z+idx*0x100+i*0x4, 0);

		for (i = 0; i < 8; i++)
			hw_write_20kx(hw, SRCDN1Z+idx*0x100+i*0x4, 0);

		ctl->dirty.bf.czbfs = 0;
	}
	if (ctl->dirty.bf.mpr) {


		unsigned int pm_idx = src_param_pitch_mixer(idx);
		hw_write_20kx(hw, PRING_LO_HI+4*pm_idx, ctl->mpr);
		hw_write_20kx(hw, PMOPLO+8*pm_idx, 0x3);
		hw_write_20kx(hw, PMOPHI+8*pm_idx, 0x0);
		ctl->dirty.bf.mpr = 0;
	}
	if (ctl->dirty.bf.sa) {
		hw_write_20kx(hw, SRCSA+idx*0x100, ctl->sa);
		ctl->dirty.bf.sa = 0;
	}
	if (ctl->dirty.bf.la) {
		hw_write_20kx(hw, SRCLA+idx*0x100, ctl->la);
		ctl->dirty.bf.la = 0;
	}
	if (ctl->dirty.bf.ca) {
		hw_write_20kx(hw, SRCCA+idx*0x100, ctl->ca);
		ctl->dirty.bf.ca = 0;
	}


	hw_write_20kx(hw, SRCCF+idx*0x100, 0x0);

	if (ctl->dirty.bf.ccr) {
		hw_write_20kx(hw, SRCCCR+idx*0x100, ctl->ccr);
		ctl->dirty.bf.ccr = 0;
	}
	if (ctl->dirty.bf.ctl) {
		hw_write_20kx(hw, SRCCTL+idx*0x100, ctl->ctl);
		ctl->dirty.bf.ctl = 0;
	}

	return 0;
}
