setup_elsa_pcmcia(struct IsdnCard *card)
{
	struct IsdnCardState *cs = card->cs;
	u_char val;

	cs->hw.elsa.base = card->para[1];
	cs->irq = card->para[0];
	val = readreg(cs->hw.elsa.base + 0, cs->hw.elsa.base + 2, IPAC_ID);
	if ((val == 1) || (val == 2)) {
		cs->subtyp = ELSA_PCMCIA_IPAC;
		cs->hw.elsa.ale = cs->hw.elsa.base + 0;
		cs->hw.elsa.isac = cs->hw.elsa.base + 2;
		cs->hw.elsa.hscx = cs->hw.elsa.base + 2;
		test_and_set_bit(HW_IPAC, &cs->HW_Flags);
	} else {
		cs->subtyp = ELSA_PCMCIA;
		cs->hw.elsa.ale = cs->hw.elsa.base + ELSA_ALE_PCM;
		cs->hw.elsa.isac = cs->hw.elsa.base + ELSA_ISAC_PCM;
		cs->hw.elsa.hscx = cs->hw.elsa.base + ELSA_HSCX;
	}
	cs->hw.elsa.timer = 0;
	cs->hw.elsa.trig = 0;
	cs->hw.elsa.ctrl = 0;
	cs->irq_flags |= IRQF_SHARED;
	printk(KERN_INFO
	       "Elsa: %s defined at %#lx IRQ %d\n",
	       Elsa_Types[cs->subtyp],
	       cs->hw.elsa.base,
	       cs->irq);
}
