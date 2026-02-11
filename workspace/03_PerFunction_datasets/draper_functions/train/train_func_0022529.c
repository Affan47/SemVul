oslec_flush(struct oslec_state *ec)
{
	int i;

	ec->ltxacc = ec->lrxacc = ec->lcleanacc = ec->lclean_bgacc = 0;
	ec->ltx = ec->lrx = ec->lclean = ec->lclean_bg = 0;
	ec->tx_1 = ec->tx_2 = ec->rx_1 = ec->rx_2 = 0;

	ec->lbgn = ec->lbgn_acc = 0;
	ec->lbgn_upper = 200;
	ec->lbgn_upper_acc = ec->lbgn_upper << 13;

	ec->nonupdate_dwell = 0;

	fir16_flush(&ec->fir_state);
	fir16_flush(&ec->fir_state_bg);
	ec->fir_state.curr_pos = ec->taps - 1;
	ec->fir_state_bg.curr_pos = ec->taps - 1;
	for (i = 0; i < 2; i++)
		memset(ec->fir_taps16[i], 0, ec->taps * sizeof(int16_t));

	ec->curr_pos = ec->taps - 1;
	ec->pstates = 0;
}
