cs5535_mfgpt_set_irq(struct cs5535_mfgpt_timer *timer, int cmp, int *irq,
		int enable)
{
	uint32_t zsel, lpc, dummy;
	int shift;

	if (!timer) {
		WARN_ON(1);
		return -EIO;
	}


	rdmsr(MSR_PIC_ZSEL_LOW, zsel, dummy);
	shift = ((cmp == MFGPT_CMP1 ? 0 : 4) + timer->nr % 4) * 4;
	if (((zsel >> shift) & 0xF) == 2)
		return -EIO;


	if (!*irq)
		*irq = (zsel >> shift) & 0xF;
	if (!*irq)
		*irq = CONFIG_CS5535_MFGPT_DEFAULT_IRQ;


	if (*irq < 1 || *irq == 2 || *irq > 15)
		return -EIO;
	rdmsr(MSR_PIC_IRQM_LPC, lpc, dummy);
	if (lpc & (1 << *irq))
		return -EIO;


	if (cs5535_mfgpt_toggle_event(timer, cmp, MFGPT_EVENT_IRQ, enable))
		return -EIO;
	if (enable) {
		zsel = (zsel & ~(0xF << shift)) | (*irq << shift);
		wrmsr(MSR_PIC_ZSEL_LOW, zsel, dummy);
	}

	return 0;
}
