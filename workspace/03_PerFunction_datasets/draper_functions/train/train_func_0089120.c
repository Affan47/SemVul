ql_update_stats(struct ql_adapter *qdev)
{
	u32 i;
	u64 data;
	u64 *iter = &qdev->nic_stats.tx_pkts;

	spin_lock(&qdev->stats_lock);
	if (ql_sem_spinlock(qdev, qdev->xg_sem_mask)) {
			netif_err(qdev, drv, qdev->ndev,
				  "Couldn't get xgmac sem.\n");
		goto quit;
	}


	for (i = 0x200; i < 0x280; i += 8) {
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else
			*iter = data;
		iter++;
	}


	for (i = 0x300; i < 0x3d0; i += 8) {
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else
			*iter = data;
		iter++;
	}


	iter += QLGE_RCV_MAC_ERR_STATS;


	for (i = 0x500; i < 0x540; i += 8) {
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else
			*iter = data;
		iter++;
	}


	for (i = 0x568; i < 0x5a8; i += 8) {
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else
			*iter = data;
		iter++;
	}


	if (ql_read_xgmac_reg64(qdev, 0x5b8, &data)) {
		netif_err(qdev, drv, qdev->ndev,
			  "Error reading status register 0x%.04x.\n", i);
		goto end;
	} else
		*iter = data;
end:
	ql_sem_unlock(qdev, qdev->xg_sem_mask);
quit:
	spin_unlock(&qdev->stats_lock);

	QL_DUMP_STAT(qdev);
}
