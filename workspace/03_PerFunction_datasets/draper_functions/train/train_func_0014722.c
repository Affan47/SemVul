aac_src_restart_adapter(struct aac_dev *dev, int bled)
{
	u32 var, reset_mask;

	if (bled >= 0) {
		if (bled)
			printk(KERN_ERR "%s%d: adapter kernel panic'd %x.\n",
				dev->name, dev->id, bled);
		dev->a_ops.adapter_enable_int = aac_src_disable_interrupt;
		bled = aac_adapter_sync_cmd(dev, IOP_RESET_ALWAYS,
			0, 0, 0, 0, 0, 0, &var, &reset_mask, NULL, NULL, NULL);
		if ((bled || (var != 0x00000001)) &&
		    !dev->doorbell_mask)
			return -EINVAL;
		else if (dev->doorbell_mask) {
			reset_mask = dev->doorbell_mask;
			bled = 0;
			var = 0x00000001;
		}

		if ((dev->pdev->device == PMC_DEVICE_S7 ||
		    dev->pdev->device == PMC_DEVICE_S8 ||
		    dev->pdev->device == PMC_DEVICE_S9) && dev->msi_enabled) {
			aac_src_access_devreg(dev, AAC_ENABLE_INTX);
			dev->msi_enabled = 0;
			msleep(5000);
		}

		if (!bled && (dev->supplement_adapter_info.SupportedOptions2 &
		    AAC_OPTION_DOORBELL_RESET)) {
			src_writel(dev, MUnit.IDR, reset_mask);
			ssleep(45);
		} else {
			src_writel(dev, MUnit.IDR, 0x100);
			ssleep(45);
		}
	}

	if (src_readl(dev, MUnit.OMR) & KERNEL_PANIC)
		return -ENODEV;

	if (startup_timeout < 300)
		startup_timeout = 300;

	return 0;
}
