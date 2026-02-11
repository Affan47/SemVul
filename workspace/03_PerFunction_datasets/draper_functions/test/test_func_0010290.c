ath_dynack_compute_ackto(struct ath_hw *ah)
{
	struct ath_node *an;
	u32 to = 0;
	struct ath_dynack *da = &ah->dynack;
	struct ath_common *common = ath9k_hw_common(ah);

	list_for_each_entry(an, &da->nodes, list)
		if (an->ackto > to)
			to = an->ackto;

	if (to && da->ackto != to) {
		u32 slottime;

		slottime = (to - 3) / 2;
		da->ackto = to;
		ath_dbg(common, DYNACK, "ACK timeout %u slottime %u\n",
			da->ackto, slottime);
		ath9k_hw_setslottime(ah, slottime);
		ath9k_hw_set_ack_timeout(ah, da->ackto);
		ath9k_hw_set_cts_timeout(ah, da->ackto);
	}
}
