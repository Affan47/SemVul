fdp_nci_post_setup(struct nci_dev *ndev)
{
	struct fdp_nci_info *info = nci_get_drvdata(ndev);
	struct device *dev = &info->phy->i2c_dev->dev;
	int r;


	if (info->fw_vsc_cfg && info->fw_vsc_cfg[0]) {


		r = fdp_nci_set_production_data(ndev, info->fw_vsc_cfg[3],
						&info->fw_vsc_cfg[4]);
		if (r) {
			nfc_err(dev, "Vendor specific config set error %d\n",
				r);
			return r;
		}
	}


	r = fdp_nci_set_clock(ndev, info->clock_type, info->clock_freq);
	if (r) {
		nfc_err(dev, "Clock set error %d\n", r);
		return r;
	}


	r = nci_core_reset(ndev);
	if (r)
		return r;


	return nci_core_init(ndev);
}
