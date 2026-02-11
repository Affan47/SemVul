setup_avm_a1_pcmcia(struct IsdnCard *card)
{
	u_char model, vers;
	struct IsdnCardState *cs = card->cs;
	char tmp[64];


	strcpy(tmp, avm_revision);
	printk(KERN_INFO "HiSax: AVM A1 PCMCIA driver Rev. %s\n",
	       HiSax_getrev(tmp));
	if (cs->typ != ISDN_CTYPE_A1_PCMCIA)
		return (0);

	cs->hw.avm.cfg_reg = card->para[1];
	cs->irq = card->para[0];


	byteout(cs->hw.avm.cfg_reg + ASL1_OFFSET, ASL1_W_ENABLE_S0);
	byteout(cs->hw.avm.cfg_reg + ASL0_OFFSET, 0x00);
	HZDELAY(HZ / 5 + 1);
	byteout(cs->hw.avm.cfg_reg + ASL0_OFFSET, ASL0_W_RESET);
	HZDELAY(HZ / 5 + 1);
	byteout(cs->hw.avm.cfg_reg + ASL0_OFFSET, 0x00);

	byteout(cs->hw.avm.cfg_reg + ASL0_OFFSET, ASL0_W_TDISABLE | ASL0_W_TRESET);

	model = bytein(cs->hw.avm.cfg_reg + MODREG_OFFSET);
	vers = bytein(cs->hw.avm.cfg_reg + VERREG_OFFSET);

	printk(KERN_INFO "AVM A1 PCMCIA: io 0x%x irq %d model %d version %d\n",
	       cs->hw.avm.cfg_reg, cs->irq, model, vers);

	setup_isac(cs);
	cs->readisac = &ReadISAC;
	cs->writeisac = &WriteISAC;
	cs->readisacfifo = &ReadISACfifo;
	cs->writeisacfifo = &WriteISACfifo;
	cs->BC_Read_Reg = &ReadHSCX;
	cs->BC_Write_Reg = &WriteHSCX;
	cs->BC_Send_Data = &hscx_fill_fifo;
	cs->cardmsg = &AVM_card_msg;
	cs->irq_flags = IRQF_SHARED;
	cs->irq_func = &avm_a1p_interrupt;

	ISACVersion(cs, "AVM A1 PCMCIA:");
	if (HscxVersion(cs, "AVM A1 PCMCIA:")) {
		printk(KERN_WARNING
		       "AVM A1 PCMCIA: wrong HSCX versions check IO address\n");
		return (0);
	}
	return (1);
}
