print_mp_irq_info(struct mpc_intsrc *mp_irq)
{
	apic_printk(APIC_VERBOSE,
		"Int: type %d, pol %d, trig %d, bus %02x, IRQ %02x, APIC ID %x, APIC INT %02x\n",
		mp_irq->irqtype, mp_irq->irqflag & 3,
		(mp_irq->irqflag >> 2) & 3, mp_irq->srcbus,
		mp_irq->srcbusirq, mp_irq->dstapic, mp_irq->dstirq);
}
