i801_check_pre(struct i801_priv *priv)
{
	int status;

	status = inb_p(SMBHSTSTS(priv));
	if (status & SMBHSTSTS_HOST_BUSY) {
		dev_err(&priv->pci_dev->dev, "SMBus is busy, can't use it!\n");
		return -EBUSY;
	}

	status &= STATUS_FLAGS;
	if (status) {
		dev_dbg(&priv->pci_dev->dev, "Clearing status flags (%02x)\n",
			status);
		outb_p(status, SMBHSTSTS(priv));
		status = inb_p(SMBHSTSTS(priv)) & STATUS_FLAGS;
		if (status) {
			dev_err(&priv->pci_dev->dev,
				"Failed clearing status flags (%02x)\n",
				status);
			return -EBUSY;
		}
	}

	return 0;
}
