s2io_updt_stats(struct s2io_nic *sp)
{
	struct XENA_dev_config __iomem *bar0 = sp->bar0;
	u64 val64;
	int cnt = 0;

	if (is_s2io_card_up(sp)) {

		val64 = SET_UPDT_CLICKS(10) |
			STAT_CFG_ONE_SHOT_EN | STAT_CFG_STAT_EN;
		writeq(val64, &bar0->stat_cfg);
		do {
			udelay(100);
			val64 = readq(&bar0->stat_cfg);
			if (!(val64 & s2BIT(0)))
				break;
			cnt++;
			if (cnt == 5)
				break;
		} while (1);
	}
}
