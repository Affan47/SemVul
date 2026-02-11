netup_unidvb_ci_unregister(struct netup_unidvb_dev *dev, int num)
{
	struct netup_ci_state *state;

	dev_dbg(&dev->pci_dev->dev, "%s()\n", __func__);
	if (num < 0 || num > 1) {
		dev_err(&dev->pci_dev->dev, "%s(): invalid CI adapter %d\n",
				__func__, num);
		return;
	}
	state = &dev->ci[num];
	dvb_ca_en50221_release(&state->ca);
}
