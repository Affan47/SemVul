dbusy_timer_handler(struct isac_hw *isac)
{
	int rbch, star;
	u_long flags;

	if (test_bit(FLG_BUSY_TIMER, &isac->dch.Flags)) {
		spin_lock_irqsave(isac->hwlock, flags);
		rbch = ReadISAC(isac, ISAC_RBCH);
		star = ReadISAC(isac, ISAC_STAR);
		pr_debug("%s: D-Channel Busy RBCH %02x STAR %02x\n",
			 isac->name, rbch, star);
		if (rbch & ISAC_RBCH_XAC)
			test_and_set_bit(FLG_L1_BUSY, &isac->dch.Flags);
		else {

			test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags);
			if (isac->dch.tx_idx)
				isac->dch.tx_idx = 0;
			else
				pr_info("%s: ISAC D-Channel Busy no tx_idx\n",
					isac->name);

			WriteISAC(isac, ISAC_CMDR, 0x01);
		}
		spin_unlock_irqrestore(isac->hwlock, flags);
	}
}
