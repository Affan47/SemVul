snd_emu10k1_ptr20_write(struct snd_emu10k1 *emu,
				   unsigned int reg,
				   unsigned int chn,
				   unsigned int data)
{
	unsigned int regptr;
	unsigned long flags;

	regptr = (reg << 16) | chn;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(regptr, emu->port + 0x20 + PTR);
	outl(data, emu->port + 0x20 + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
}
