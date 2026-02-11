bch_empty_fifo(struct BCState *bcs, int count)
{
	u_char *ptr, hscx;
	struct IsdnCardState *cs;
	int cnt;

	cs = bcs->cs;
	hscx = bcs->hw.hscx.hscx;
	if ((cs->debug & L1_DEB_HSCX) && !(cs->debug & L1_DEB_HSCX_FIFO))
		debugl1(cs, "bch_empty_fifo()");


	if (bcs->hw.hscx.rcvidx + count > HSCX_BUFMAX) {
		if (cs->debug & L1_DEB_WARN)
			debugl1(cs, "bch_empty_fifo() incoming packet too large");
		cs->BC_Write_Reg(cs, hscx, IPACX_CMDRB, 0x80);
		bcs->hw.hscx.rcvidx = 0;
		return;
	}

	ptr = bcs->hw.hscx.rcvbuf + bcs->hw.hscx.rcvidx;
	cnt = count;
	while (cnt--) *ptr++ = cs->BC_Read_Reg(cs, hscx, IPACX_RFIFOB);
	cs->BC_Write_Reg(cs, hscx, IPACX_CMDRB, 0x80);

	ptr = bcs->hw.hscx.rcvbuf + bcs->hw.hscx.rcvidx;
	bcs->hw.hscx.rcvidx += count;

	if (cs->debug & L1_DEB_HSCX_FIFO) {
		char *t = bcs->blog;

		t += sprintf(t, "bch_empty_fifo() B-%d cnt %d", hscx, count);
		QuickHex(t, ptr, count);
		debugl1(cs, "%s", bcs->blog);
	}
}
