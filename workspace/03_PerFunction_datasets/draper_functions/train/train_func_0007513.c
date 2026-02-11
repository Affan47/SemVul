pn544_hci_open(struct nfc_hci_dev *hdev)
{
	struct pn544_hci_info *info = nfc_hci_get_clientdata(hdev);
	int r = 0;

	mutex_lock(&info->info_lock);

	if (info->state != PN544_ST_COLD) {
		r = -EBUSY;
		goto out;
	}

	r = info->phy_ops->enable(info->phy_id);

	if (r == 0)
		info->state = PN544_ST_READY;

out:
	mutex_unlock(&info->info_lock);
	return r;
}
