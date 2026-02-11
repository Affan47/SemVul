snd_vx_irq_handler(int irq, void *dev)
{
	struct vx_core *chip = dev;

	if (! (chip->chip_status & VX_STAT_CHIP_INIT) ||
	    (chip->chip_status & VX_STAT_IS_STALE))
		return IRQ_NONE;
	if (! vx_test_and_ack(chip))
		return IRQ_WAKE_THREAD;
	return IRQ_NONE;
}
