isac_retransmit(struct isac_hw *isac)
{
	if (test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags))
		del_timer(&isac->dch.timer);
	if (test_bit(FLG_TX_BUSY, &isac->dch.Flags)) {

		isac->dch.tx_idx = 0;
		isac_fill_fifo(isac);
	} else if (isac->dch.tx_skb) {
		pr_info("%s: tx_skb exist but not busy\n", isac->name);
		test_and_set_bit(FLG_TX_BUSY, &isac->dch.Flags);
		isac->dch.tx_idx = 0;
		isac_fill_fifo(isac);
	} else {
		pr_info("%s: ISAC XDU no TX_BUSY\n", isac->name);
		if (get_next_dframe(&isac->dch))
			isac_fill_fifo(isac);
	}
}
