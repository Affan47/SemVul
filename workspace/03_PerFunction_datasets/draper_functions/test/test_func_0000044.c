brcmstb_i2c_isr(int irq, void *devid)
{
	struct brcmstb_i2c_dev *dev = devid;
	u32 status_bsc_ctl = bsc_readl(dev, ctl_reg);
	u32 status_iic_intrp = bsc_readl(dev, iic_enable);

	dev_dbg(dev->device, "isr CTL_REG %x IIC_EN %x\n",
		status_bsc_ctl, status_iic_intrp);

	if (!(status_bsc_ctl & BSC_CTL_REG_INT_EN_MASK))
		return IRQ_NONE;

	brcmstb_i2c_enable_disable_irq(dev, INT_DISABLE);
	complete_all(&dev->done);

	dev_dbg(dev->device, "isr handled");
	return IRQ_HANDLED;
}
