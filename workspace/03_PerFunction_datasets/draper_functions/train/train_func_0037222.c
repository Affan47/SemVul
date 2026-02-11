tpci200_interrupt(int irq, void *dev_id)
{
	struct tpci200_board *tpci200 = (struct tpci200_board *) dev_id;
	struct slot_irq *slot_irq;
	irqreturn_t ret;
	u16 status_reg;
	int i;


	status_reg = ioread16(&tpci200->info->interface_regs->status);


	if (!(status_reg & TPCI200_SLOT_INT_MASK))
		return IRQ_NONE;


	rcu_read_lock();
	for (i = 0; i < TPCI200_NB_SLOT; i++) {
		if (!(status_reg & ((TPCI200_A_INT0 | TPCI200_A_INT1) << (2 * i))))
			continue;
		slot_irq = rcu_dereference(tpci200->slots[i].irq);
		ret = tpci200_slot_irq(slot_irq);
		if (ret == -ENODEV) {
			dev_info(&tpci200->info->pdev->dev,
				 "No registered ISR for slot [%d:%d]!. IRQ will be disabled.\n",
				 tpci200->number, i);
			tpci200_disable_irq(tpci200, i);
		}
	}
	rcu_read_unlock();

	return IRQ_HANDLED;
}
