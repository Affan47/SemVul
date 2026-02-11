i801_isr(int irq, void *dev_id)
{
	struct i801_priv *priv = dev_id;
	u16 pcists;
	u8 status;


	pci_read_config_word(priv->pci_dev, SMBPCISTS, &pcists);
	if (!(pcists & SMBPCISTS_INTS))
		return IRQ_NONE;

	status = inb_p(SMBHSTSTS(priv));
	if (status & SMBHSTSTS_BYTE_DONE)
		i801_isr_byte_done(priv);


	status &= SMBHSTSTS_INTR | STATUS_ERROR_FLAGS;
	if (status) {
		outb_p(status, SMBHSTSTS(priv));
		priv->status |= status;
		wake_up(&priv->waitq);
	}

	return IRQ_HANDLED;
}
