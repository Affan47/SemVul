dev_rssi_cmp(struct remote_dev_info *d1, struct remote_dev_info *d2)
{
	int rssi1, rssi2;

	rssi1 = d1->rssi < 0 ? -d1->rssi : d1->rssi;
	rssi2 = d2->rssi < 0 ? -d2->rssi : d2->rssi;

	return rssi1 - rssi2;
}
