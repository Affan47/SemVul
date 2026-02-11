fifo_select(struct IsdnCardState *cs, u_char fifo)
{
	if (fifo == cs->hw.hfcsx.last_fifo)
		return;

	byteout(cs->hw.hfcsx.base + 1, HFCSX_FIF_SEL);
	byteout(cs->hw.hfcsx.base, fifo);
	while (bytein(cs->hw.hfcsx.base + 1) & 1);
	udelay(4);
	byteout(cs->hw.hfcsx.base, fifo);
	while (bytein(cs->hw.hfcsx.base + 1) & 1);
}
