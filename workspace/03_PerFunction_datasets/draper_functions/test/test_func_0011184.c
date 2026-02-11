ath_pci_probe(struct pci_device *pdev)
{
	void *mem;
	struct ath_softc *sc;
	struct net80211_device *dev;
	u8 csz;
	u16 subsysid;
	u32 val;
	int ret = 0;
	char hw_name[64];

	adjust_pci_device(pdev);


	pci_read_config_byte(pdev, PCI_CACHE_LINE_SIZE, &csz);
	if (csz == 0) {


		csz =16;
		pci_write_config_byte(pdev, PCI_CACHE_LINE_SIZE, csz);
	}


	pci_write_config_byte(pdev, PCI_LATENCY_TIMER, 0xa8);


	pci_read_config_dword(pdev, 0x40, &val);
	if ((val & 0x0000ff00) != 0)
		pci_write_config_dword(pdev, 0x40, val & 0xffff00ff);

	mem = ioremap(pdev->membase, 0x10000);
	if (!mem) {
		DBG("ath9K: PCI memory map error\n") ;
		ret = -EIO;
		goto err_iomap;
	}

	dev = net80211_alloc(sizeof(struct ath_softc));
	if (!dev) {
		DBG("ath9k: No memory for net80211_device\n");
		ret = -ENOMEM;
		goto err_alloc_hw;
	}

	pci_set_drvdata(pdev, dev);
	dev->netdev->dev = (struct device *)pdev;

	sc = dev->priv;
	sc->dev = dev;
	sc->pdev = pdev;
	sc->mem = mem;


	sc->sc_flags |= SC_OP_INVALID;

	sc->irq = pdev->irq;

	pci_read_config_word(pdev, PCI_SUBSYSTEM_ID, &subsysid);
	ret = ath9k_init_device(pdev->device, sc, subsysid, &ath_pci_bus_ops);
	if (ret) {
		DBG("ath9k: Failed to initialize device\n");
		goto err_init;
	}

	ath9k_hw_name(sc->sc_ah, hw_name, sizeof(hw_name));
	DBG("ath9k: %s mem=0x%lx, irq=%d\n",
		   hw_name, (unsigned long)mem, pdev->irq);

	return 0;

err_init:
	net80211_free(dev);
err_alloc_hw:
	iounmap(mem);
err_iomap:
	return ret;
}
