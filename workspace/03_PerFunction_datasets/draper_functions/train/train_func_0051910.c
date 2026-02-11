dai_commit_write(struct hw *hw, unsigned int idx, void *blk)
{
	struct dai_ctrl_blk *ctl = blk;

	if (ctl->dirty.bf.srtctl) {
		if (idx < 4) {

			hw_write_20kx(hw, SRTSCTL+0x4*idx, ctl->srtctl);
		} else {

			hw_write_20kx(hw, SRTICTL, ctl->srtctl);
		}
		ctl->dirty.bf.srtctl = 0;
	}

	return 0;
}
