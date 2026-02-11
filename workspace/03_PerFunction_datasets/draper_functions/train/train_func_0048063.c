enpci_interrupt(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	unsigned char s0val, s1val, ir;
	u_long flags;

	spin_lock_irqsave(&cs->lock, flags);
	s1val = inb(cs->hw.njet.base + NETJET_IRQSTAT1);


	if (!(s1val & TJ_AMD_IRQ)) {

		ir = ReadByteAmd7930(cs, 0x00);
		Amd7930_interrupt(cs, ir);
		s1val = 1;
	} else
		s1val = 0;
	s0val = inb(cs->hw.njet.base + NETJET_IRQSTAT0);
	if ((s0val | s1val) == 0) {
		spin_unlock_irqrestore(&cs->lock, flags);
		return IRQ_NONE;
	}
	if (s0val)
		outb(s0val, cs->hw.njet.base + NETJET_IRQSTAT0);


	if (inl(cs->hw.njet.base + NETJET_DMA_WRITE_ADR) <
	    inl(cs->hw.njet.base + NETJET_DMA_WRITE_IRQ))

		s0val = 0x08;
	else
		s0val = 0x04;
	if (inl(cs->hw.njet.base + NETJET_DMA_READ_ADR) <
	    inl(cs->hw.njet.base + NETJET_DMA_READ_IRQ))

		s0val = s0val | 0x02;
	else
		s0val = s0val | 0x01;
	if (s0val != cs->hw.njet.last_is0)
	{
		if (test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
			spin_unlock_irqrestore(&cs->lock, flags);
			return IRQ_HANDLED;
		}
		cs->hw.njet.irqstat0 = s0val;
		if ((cs->hw.njet.irqstat0 & NETJET_IRQM0_READ) !=
		    (cs->hw.njet.last_is0 & NETJET_IRQM0_READ))

			read_tiger(cs);
		if ((cs->hw.njet.irqstat0 & NETJET_IRQM0_WRITE) !=
		    (cs->hw.njet.last_is0 & NETJET_IRQM0_WRITE))

			write_tiger(cs);
		test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
	}
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}
