ia_start(struct atm_dev *dev)
{
	IADEV *iadev;
	int error;
	unsigned char phy;
	u32 ctrl_reg;
	IF_EVENT(printk(">ia_start\n");)
	iadev = INPH_IA_DEV(dev);
        if (request_irq(iadev->irq, &ia_int, IRQF_SHARED, DEV_LABEL, dev)) {
                printk(KERN_ERR DEV_LABEL "(itf %d): IRQ%d is already in use\n",
                    dev->number, iadev->irq);
		error = -EAGAIN;
		goto err_out;
        }


        if ((error = pci_write_config_word(iadev->pci,
				PCI_COMMAND,
				PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER )))
	{
                printk(KERN_ERR DEV_LABEL "(itf %d): can't enable memory+"
                    "master (0x%x)\n",dev->number, error);
		error = -EIO;
		goto err_free_irq;
        }
	udelay(10);


	IF_INIT(printk("Bus ctrl reg: %08x\n",
                            readl(iadev->reg+IPHASE5575_BUS_CONTROL_REG));)
	ctrl_reg = readl(iadev->reg+IPHASE5575_BUS_CONTROL_REG);
	ctrl_reg = (ctrl_reg & (CTRL_LED | CTRL_FE_RST))
			| CTRL_B8
			| CTRL_B16
			| CTRL_B32
			| CTRL_B48
			| CTRL_B64
			| CTRL_B128
			| CTRL_ERRMASK
			| CTRL_DLETMASK
			| CTRL_DLERMASK
			| CTRL_SEGMASK
			| CTRL_REASSMASK
			| CTRL_FEMASK
			| CTRL_CSPREEMPT;

       writel(ctrl_reg, iadev->reg+IPHASE5575_BUS_CONTROL_REG);

	IF_INIT(printk("Bus ctrl reg after initializing: %08x\n",
                           readl(iadev->reg+IPHASE5575_BUS_CONTROL_REG));
	   printk("Bus status reg after init: %08x\n",
                            readl(iadev->reg+IPHASE5575_BUS_STATUS_REG));)

        ia_hw_type(iadev);
	error = tx_init(dev);
	if (error)
		goto err_free_irq;
	error = rx_init(dev);
	if (error)
		goto err_free_tx;

	ctrl_reg = readl(iadev->reg+IPHASE5575_BUS_CONTROL_REG);
       	writel(ctrl_reg | CTRL_FE_RST, iadev->reg+IPHASE5575_BUS_CONTROL_REG);
	IF_INIT(printk("Bus ctrl reg after initializing: %08x\n",
                               readl(iadev->reg+IPHASE5575_BUS_CONTROL_REG));)
        phy = 0;
        IF_INIT (
	if ((phy=ia_phy_get(dev,0)) == 0x30)
		printk("IA: pm5346,rev.%d\n",phy&0x0f);
	else
		printk("IA: utopia,rev.%0x\n",phy);)

	if (iadev->phy_type &  FE_25MBIT_PHY)
           ia_mb25_init(iadev);
	else if (iadev->phy_type & (FE_DS3_PHY | FE_E3_PHY))
           ia_suni_pm7345_init(iadev);
	else {
		error = suni_init(dev);
		if (error)
			goto err_free_rx;
		if (dev->phy->start) {
			error = dev->phy->start(dev);
			if (error)
				goto err_free_rx;
		}

		ia_frontend_intr(iadev);
	}
	return 0;

err_free_rx:
	ia_free_rx(iadev);
err_free_tx:
	ia_free_tx(iadev);
err_free_irq:
	free_irq(iadev->irq, dev);
err_out:
	return error;
}
