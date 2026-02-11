oaktrail_hdmi_setup(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct pci_dev *pdev;
	struct oaktrail_hdmi_dev *hdmi_dev;
	int ret;

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x080d, NULL);
	if (!pdev)
		return;

	hdmi_dev = kzalloc(sizeof(struct oaktrail_hdmi_dev), GFP_KERNEL);
	if (!hdmi_dev) {
		dev_err(dev->dev, "failed to allocate memory\n");
		goto out;
	}


	ret = pci_enable_device(pdev);
	if (ret) {
		dev_err(dev->dev, "failed to enable hdmi controller\n");
		goto free;
	}

	hdmi_dev->mmio = pci_resource_start(pdev, 0);
	hdmi_dev->mmio_len = pci_resource_len(pdev, 0);
	hdmi_dev->regs = ioremap(hdmi_dev->mmio, hdmi_dev->mmio_len);
	if (!hdmi_dev->regs) {
		dev_err(dev->dev, "failed to map hdmi mmio\n");
		goto free;
	}

	hdmi_dev->dev = pdev;
	pci_set_drvdata(pdev, hdmi_dev);


	ret = oaktrail_hdmi_i2c_init(hdmi_dev->dev);
	if (ret)
		dev_err(dev->dev, "HDMI I2C initialization failed\n");

	dev_priv->hdmi_priv = hdmi_dev;
	oaktrail_hdmi_audio_disable(dev);

	dev_info(dev->dev, "HDMI hardware present.\n");

	return;

free:
	kfree(hdmi_dev);
out:
	return;
}
