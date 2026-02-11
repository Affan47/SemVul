__pcf50633_irq_mask_set(struct pcf50633 *pcf, int irq, u8 mask)
{
	u8 reg, bit;
	int idx;

	idx = irq >> 3;
	reg = PCF50633_REG_INT1M + idx;
	bit = 1 << (irq & 0x07);

	pcf50633_reg_set_bit_mask(pcf, reg, bit, mask ? bit : 0);

	mutex_lock(&pcf->lock);

	if (mask)
		pcf->mask_regs[idx] |= bit;
	else
		pcf->mask_regs[idx] &= ~bit;

	mutex_unlock(&pcf->lock);

	return 0;
}
