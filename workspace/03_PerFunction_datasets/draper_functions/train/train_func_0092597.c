pci_conf1(void)
{
	unsigned long flags;
	u32 tmp;

	spin_lock_irqsave(&cmd640_lock, flags);
	outb(0x01, 0xCFB);
	tmp = inl(0xCF8);
	outl(0x80000000, 0xCF8);
	if (inl(0xCF8) == 0x80000000) {
		outl(tmp, 0xCF8);
		spin_unlock_irqrestore(&cmd640_lock, flags);
		return 1;
	}
	outl(tmp, 0xCF8);
	spin_unlock_irqrestore(&cmd640_lock, flags);
	return 0;
}
