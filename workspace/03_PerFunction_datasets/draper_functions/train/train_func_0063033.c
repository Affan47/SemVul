W6692_fill_fifo(struct IsdnCardState *cs)
{
	int count, more;
	u_char *ptr;

	if ((cs->debug & L1_DEB_ISAC) && !(cs->debug & L1_DEB_ISAC_FIFO))
		debugl1(cs, "W6692_fill_fifo");

	if (!cs->tx_skb)
		return;

	count = cs->tx_skb->len;
	if (count <= 0)
		return;

	more = 0;
	if (count > W_D_FIFO_THRESH) {
		more = !0;
		count = W_D_FIFO_THRESH;
	}
	ptr = cs->tx_skb->data;
	skb_pull(cs->tx_skb, count);
	cs->tx_cnt += count;
	cs->writeW6692fifo(cs, ptr, count);
	cs->writeW6692(cs, W_D_CMDR, more ? W_D_CMDR_XMS : (W_D_CMDR_XMS | W_D_CMDR_XME));
	if (test_and_set_bit(FLG_DBUSY_TIMER, &cs->HW_Flags)) {
		debugl1(cs, "W6692_fill_fifo dbusytimer running");
		del_timer(&cs->dbusytimer);
	}
	init_timer(&cs->dbusytimer);
	cs->dbusytimer.expires = jiffies + ((DBUSY_TIMER_VALUE * HZ) / 1000);
	add_timer(&cs->dbusytimer);
	if (cs->debug & L1_DEB_ISAC_FIFO) {
		char *t = cs->dlog;

		t += sprintf(t, "W6692_fill_fifo cnt %d", count);
		QuickHex(t, ptr, count);
		debugl1(cs, "%s", cs->dlog);
	}
}
