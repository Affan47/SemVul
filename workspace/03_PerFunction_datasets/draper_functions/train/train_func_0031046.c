pcirom_init(struct nvkm_bios *bios, const char *name)
{
	struct nvkm_device *device = bios->subdev.device;
	struct priv *priv = NULL;
	struct pci_dev *pdev;
	int ret;

	if (device->func->pci)
		pdev = device->func->pci(device)->pdev;
	else
		return ERR_PTR(-ENODEV);

	if (!(ret = pci_enable_rom(pdev))) {
		if (ret = -ENOMEM,
		    (priv = kmalloc(sizeof(*priv), GFP_KERNEL))) {
			if (ret = -EFAULT,
			    (priv->rom = pci_map_rom(pdev, &priv->size))) {
				priv->pdev = pdev;
				return priv;
			}
			kfree(priv);
		}
		pci_disable_rom(pdev);
	}

	return ERR_PTR(ret);
}
