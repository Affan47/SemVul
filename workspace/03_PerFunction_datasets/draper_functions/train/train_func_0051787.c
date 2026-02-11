xen_pcibk_config_quirk_release(struct pci_dev *dev)
{
	struct xen_pcibk_config_quirk *quirk;
	int ret = 0;

	quirk = xen_pcibk_find_quirk(dev);
	if (!quirk) {
		ret = -ENXIO;
		goto out;
	}

	list_del(&quirk->quirks_list);
	kfree(quirk);

out:
	return ret;
}
