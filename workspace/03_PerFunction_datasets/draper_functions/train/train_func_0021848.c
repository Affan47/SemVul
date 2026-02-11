amixer_set_sum(struct amixer *amixer, struct sum *sum)
{
	struct hw *hw;

	hw = amixer->rsc.hw;
	amixer->sum = sum;
	if (!sum) {
		hw->amixer_set_se(amixer->rsc.ctrl_blk, 0);
	} else {
		hw->amixer_set_se(amixer->rsc.ctrl_blk, 1);
		hw->amixer_set_sadr(amixer->rsc.ctrl_blk,
					sum->rsc.ops->index(&sum->rsc));
	}

	return 0;
}
