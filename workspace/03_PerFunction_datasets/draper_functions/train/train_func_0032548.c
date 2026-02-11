read_delin(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	int ret = -ENODEV;
	struct uea_softc *sc;
	char *delin = "GOOD";

	mutex_lock(&uea_mutex);
	sc = dev_to_uea(dev);
	if (!sc)
		goto out;

	if (UEA_CHIP_VERSION(sc) == EAGLE_IV) {
		if (sc->stats.phy.flags & 0x4000)
			delin = "RESET";
		else if (sc->stats.phy.flags & 0x0001)
			delin = "LOSS";
	} else {
		if (sc->stats.phy.flags & 0x0C00)
			delin = "ERROR";
		else if (sc->stats.phy.flags & 0x0030)
			delin = "LOSS";
	}

	ret = sprintf(buf, "%s\n", delin);
out:
	mutex_unlock(&uea_mutex);
	return ret;
}
