ssb_devices_register(struct ssb_bus *bus)
{
	struct ssb_device *sdev;
	struct device *dev;
	struct __ssb_dev_wrapper *devwrap;
	int i, err = 0;
	int dev_idx = 0;

	for (i = 0; i < bus->nr_devices; i++) {
		sdev = &(bus->devices[i]);


		switch (sdev->id.coreid) {
		case SSB_DEV_CHIPCOMMON:
		case SSB_DEV_PCI:
		case SSB_DEV_PCIE:
		case SSB_DEV_PCMCIA:
		case SSB_DEV_MIPS:
		case SSB_DEV_MIPS_3302:
		case SSB_DEV_EXTIF:
			continue;
		}

		devwrap = kzalloc(sizeof(*devwrap), GFP_KERNEL);
		if (!devwrap) {
			ssb_err("Could not allocate device\n");
			err = -ENOMEM;
			goto error;
		}
		dev = &devwrap->dev;
		devwrap->sdev = sdev;

		dev->release = ssb_release_dev;
		dev->bus = &ssb_bustype;
		dev_set_name(dev, "ssb%u:%d", bus->busnumber, dev_idx);

		switch (bus->bustype) {
		case SSB_BUSTYPE_PCI:
#ifdef CONFIG_SSB_PCIHOST
			sdev->irq = bus->host_pci->irq;
			dev->parent = &bus->host_pci->dev;
			sdev->dma_dev = dev->parent;
#endif
			break;
		case SSB_BUSTYPE_PCMCIA:
#ifdef CONFIG_SSB_PCMCIAHOST
			sdev->irq = bus->host_pcmcia->irq;
			dev->parent = &bus->host_pcmcia->dev;
#endif
			break;
		case SSB_BUSTYPE_SDIO:
#ifdef CONFIG_SSB_SDIOHOST
			dev->parent = &bus->host_sdio->dev;
#endif
			break;
		case SSB_BUSTYPE_SSB:
			dev->dma_mask = &dev->coherent_dma_mask;
			sdev->dma_dev = dev;
			break;
		}

		sdev->dev = dev;
		err = device_register(dev);
		if (err) {
			ssb_err("Could not register %s\n", dev_name(dev));


			sdev->dev = NULL;
			kfree(devwrap);
			goto error;
		}
		dev_idx++;
	}

#ifdef CONFIG_SSB_DRIVER_MIPS
	if (bus->mipscore.pflash.present) {
		err = platform_device_register(&ssb_pflash_dev);
		if (err)
			pr_err("Error registering parallel flash\n");
	}
#endif

#ifdef CONFIG_SSB_SFLASH
	if (bus->mipscore.sflash.present) {
		err = platform_device_register(&ssb_sflash_dev);
		if (err)
			pr_err("Error registering serial flash\n");
	}
#endif

	return 0;
error:

	ssb_devices_unregister(bus);
	return err;
}
