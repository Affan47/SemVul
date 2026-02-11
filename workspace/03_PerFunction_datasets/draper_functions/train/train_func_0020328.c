sedlbauer_interrupt_isar(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	u_char val;
	int cnt = 5;
	u_long flags;

	spin_lock_irqsave(&cs->lock, flags);
	val = readreg(cs->hw.sedl.adr, cs->hw.sedl.hscx, ISAR_IRQBIT);
Start_ISAR:
	if (val & ISAR_IRQSTA)
		isar_int_main(cs);
	val = readreg(cs->hw.sedl.adr, cs->hw.sedl.isac, ISAC_ISTA);
Start_ISAC:
	if (val)
		isac_interrupt(cs, val);
	val = readreg(cs->hw.sedl.adr, cs->hw.sedl.hscx, ISAR_IRQBIT);
	if ((val & ISAR_IRQSTA) && --cnt) {
		if (cs->debug & L1_DEB_HSCX)
			debugl1(cs, "ISAR IntStat after IntRoutine");
		goto Start_ISAR;
	}
	val = readreg(cs->hw.sedl.adr, cs->hw.sedl.isac, ISAC_ISTA);
	if (val && --cnt) {
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "ISAC IntStat after IntRoutine");
		goto Start_ISAC;
	}
	if (!cnt)
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "Sedlbauer IRQ LOOP");

	writereg(cs->hw.sedl.adr, cs->hw.sedl.hscx, ISAR_IRQBIT, 0);
	writereg(cs->hw.sedl.adr, cs->hw.sedl.isac, ISAC_MASK, 0xFF);
	writereg(cs->hw.sedl.adr, cs->hw.sedl.isac, ISAC_MASK, 0x0);
	writereg(cs->hw.sedl.adr, cs->hw.sedl.hscx, ISAR_IRQBIT, ISAR_IRQMSK);
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}
