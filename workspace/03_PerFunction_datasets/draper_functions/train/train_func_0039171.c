qib_7322_set_loopback(struct qib_pportdata *ppd, const char *what)
{
	int ret = 0;
	u64 val, ctrlb;


	if (!strncmp(what, "ibc", 3)) {
		ppd->cpspec->ibcctrl_a |= SYM_MASK(IBCCtrlA_0,
						       Loopback);
		val = 0;
		qib_devinfo(ppd->dd->pcidev, "Enabling IB%u:%u IBC loopback\n",
			 ppd->dd->unit, ppd->port);
	} else if (!strncmp(what, "off", 3)) {
		ppd->cpspec->ibcctrl_a &= ~SYM_MASK(IBCCtrlA_0,
							Loopback);

		val = IBA7322_IBC_HRTBT_RMASK << IBA7322_IBC_HRTBT_LSB;
		qib_devinfo(ppd->dd->pcidev,
			"Disabling IB%u:%u IBC loopback (normal)\n",
			ppd->dd->unit, ppd->port);
	} else
		ret = -EINVAL;
	if (!ret) {
		qib_write_kreg_port(ppd, krp_ibcctrl_a,
				    ppd->cpspec->ibcctrl_a);
		ctrlb = ppd->cpspec->ibcctrl_b & ~(IBA7322_IBC_HRTBT_MASK
					     << IBA7322_IBC_HRTBT_LSB);
		ppd->cpspec->ibcctrl_b = ctrlb | val;
		qib_write_kreg_port(ppd, krp_ibcctrl_b,
				    ppd->cpspec->ibcctrl_b);
		qib_write_kreg(ppd->dd, kr_scratch, 0);
	}
	return ret;
}
