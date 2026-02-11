init_card(struct IsdnCardState *cs)
{
	int	irq_cnt, cnt = 3, ret;

	if (!cs->irq) {
		ret = cs->cardmsg(cs, CARD_INIT, NULL);
		return (ret);
	}
	irq_cnt = cs->irq_cnt = 0;
	printk(KERN_INFO "%s: IRQ %d count %d\n", CardType[cs->typ],
	       cs->irq, irq_cnt);
	if (request_irq(cs->irq, card_irq, cs->irq_flags, "HiSax", cs)) {
		printk(KERN_WARNING "HiSax: couldn't get interrupt %d\n",
		       cs->irq);
		return 1;
	}
	while (cnt) {
		cs->cardmsg(cs, CARD_INIT, NULL);

		msleep(10);
		printk(KERN_INFO "%s: IRQ %d count %d\n",
		       CardType[cs->typ], cs->irq, cs->irq_cnt);
		if (cs->irq_cnt == irq_cnt) {
			printk(KERN_WARNING
			       "%s: IRQ(%d) getting no interrupts during init %d\n",
			       CardType[cs->typ], cs->irq, 4 - cnt);
			if (cnt == 1) {
				free_irq(cs->irq, cs);
				return 2;
			} else {
				cs->cardmsg(cs, CARD_RESET, NULL);
				cnt--;
			}
		} else {
			cs->cardmsg(cs, CARD_TEST, NULL);
			return 0;
		}
	}
	return 3;
}
