name_msix_vecs(struct adapter *adap)
{
	int i, j, msi_idx = 1, n = sizeof(adap->msix_info[0].desc) - 1;

	snprintf(adap->msix_info[0].desc, n, "%s", adap->name);
	adap->msix_info[0].desc[n] = 0;

	for_each_port(adap, j) {
		struct net_device *d = adap->port[j];
		const struct port_info *pi = netdev_priv(d);

		for (i = 0; i < pi->nqsets; i++, msi_idx++) {
			snprintf(adap->msix_info[msi_idx].desc, n,
				 "%s-%d", d->name, pi->first_qset + i);
			adap->msix_info[msi_idx].desc[n] = 0;
		}
	}
}
