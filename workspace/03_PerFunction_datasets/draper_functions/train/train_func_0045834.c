_sc92031_mii_wait(void __iomem *port_base)
{
	u32 mii_status;

	do {
		udelay(10);
		mii_status = ioread32(port_base + Miistatus);
	} while (mii_status & Mii_StatusBusy);

	return mii_status;
}
