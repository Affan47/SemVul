lola_update_rirb(struct lola *chip)
{
	unsigned int rp, wp;
	u32 res, res_ex;

	wp = lola_readw(chip, BAR0, RIRBWP);
	if (wp == chip->rirb.wp)
		return;
	chip->rirb.wp = wp;

	while (chip->rirb.rp != wp) {
		chip->rirb.rp++;
		chip->rirb.rp %= LOLA_CORB_ENTRIES;

		rp = chip->rirb.rp << 1;
		res_ex = le32_to_cpu(chip->rirb.buf[rp + 1]);
		res = le32_to_cpu(chip->rirb.buf[rp]);
		if (res_ex & LOLA_RIRB_EX_UNSOL_EV)
			lola_queue_unsol_event(chip, res, res_ex);
		else if (chip->rirb.cmds) {
			chip->res = res;
			chip->res_ex = res_ex;
			smp_wmb();
			chip->rirb.cmds--;
		}
	}
}
