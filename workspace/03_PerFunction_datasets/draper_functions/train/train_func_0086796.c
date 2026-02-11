loop_set_carrier_report(struct rc_dev *dev, int enable)
{
	struct loopback_dev *lodev = dev->priv;

	if (lodev->carrierreport != enable) {
		dprintk("%sabling carrier reports\n", enable ? "en" : "dis");
		lodev->carrierreport = !!enable;
	}

	return 0;
}
