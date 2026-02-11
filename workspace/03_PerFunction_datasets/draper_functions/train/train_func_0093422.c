cmci_clear(void)
{
	unsigned long flags;
	int i;
	int banks;

	if (!cmci_supported(&banks))
		return;
	raw_spin_lock_irqsave(&cmci_discover_lock, flags);
	for (i = 0; i < banks; i++)
		__cmci_disable_bank(i);
	raw_spin_unlock_irqrestore(&cmci_discover_lock, flags);
}
