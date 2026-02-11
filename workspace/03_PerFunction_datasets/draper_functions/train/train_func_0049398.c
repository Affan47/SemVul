setup_elsa(struct IsdnCard *card)
{
	int rc;
	struct IsdnCardState *cs = card->cs;
	char tmp[64];

	strcpy(tmp, Elsa_revision);
	printk(KERN_INFO "HiSax: Elsa driver Rev. %s\n", HiSax_getrev(tmp));
	cs->hw.elsa.ctrl_reg = 0;
	cs->hw.elsa.status = 0;
	cs->hw.elsa.MFlag = 0;
	cs->subtyp = 0;

	if (cs->typ == ISDN_CTYPE_ELSA) {
		rc = setup_elsa_isa(card);
		if (!rc)
			return (0);

	} else if (cs->typ == ISDN_CTYPE_ELSA_PNP) {
		rc = setup_elsa_isapnp(card);
		if (!rc)
			return (0);

	} else if (cs->typ == ISDN_CTYPE_ELSA_PCMCIA)
		setup_elsa_pcmcia(card);

	else if (cs->typ == ISDN_CTYPE_ELSA_PCI) {
		rc = setup_elsa_pci(card);
		if (!rc)
			return (0);

	} else
		return (0);

	return setup_elsa_common(card);
}
