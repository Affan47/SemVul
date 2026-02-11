ipath_ht_intconfig(struct ipath_devdata *dd)
{
	int ret;

	if (dd->ipath_intconfig) {
		ipath_write_kreg(dd, dd->ipath_kregs->kr_interruptconfig,
				 dd->ipath_intconfig);
		ret = 0;
	} else {
		ipath_dev_err(dd, "No interrupts enabled, couldn't setup "
			      "interrupt address\n");
		ret = -EINVAL;
	}

	return ret;
}
