snd_emu1010_fpga_read(struct snd_emu10k1 * emu, u32 reg, u32 *value)
{
	unsigned long flags;
	if (reg > 0x3f)
		return 1;
	reg += 0x40;
	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(reg, emu->port + A_IOCFG);
	udelay(10);
	outl(reg | 0x80, emu->port + A_IOCFG);
	udelay(10);
	*value = ((inl(emu->port + A_IOCFG) >> 8) & 0x7f);
	spin_unlock_irqrestore(&emu->emu_lock, flags);

	return 0;
}
