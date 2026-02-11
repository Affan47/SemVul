tg3_halt(struct tg3 *tp, int kind, bool silent)
{
	int err;

	tg3_stop_fw(tp);

	tg3_write_sig_pre_reset(tp, kind);

	tg3_abort_hw(tp, silent);
	err = tg3_chip_reset(tp);

	__tg3_set_mac_addr(tp, false);

	tg3_write_sig_legacy(tp, kind);
	tg3_write_sig_post_reset(tp, kind);

	if (tp->hw_stats) {

		tg3_get_nstats(tp, &tp->net_stats_prev);
		tg3_get_estats(tp, &tp->estats_prev);


		memset(tp->hw_stats, 0, sizeof(struct tg3_hw_stats));
	}

	return err;
}
