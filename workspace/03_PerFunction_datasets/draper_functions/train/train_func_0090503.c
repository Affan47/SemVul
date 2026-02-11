qede_stop_queues(struct qede_dev *edev)
{
	struct qed_update_vport_params vport_update_params;
	struct qed_dev *cdev = edev->cdev;
	int rc, tc, i;


	memset(&vport_update_params, 0, sizeof(vport_update_params));
	vport_update_params.vport_id = 0;
	vport_update_params.update_vport_active_flg = 1;
	vport_update_params.vport_active_flg = 0;
	vport_update_params.update_rss_flg = 0;

	rc = edev->ops->vport_update(cdev, &vport_update_params);
	if (rc) {
		DP_ERR(edev, "Failed to update vport\n");
		return rc;
	}


	for_each_rss(i) {
		struct qede_fastpath *fp = &edev->fp_array[i];

		for (tc = 0; tc < edev->num_tc; tc++) {
			struct qede_tx_queue *txq = &fp->txqs[tc];

			rc = qede_drain_txq(edev, txq, true);
			if (rc)
				return rc;
		}
	}


	for (i = QEDE_RSS_CNT(edev) - 1; i >= 0; i--) {
		struct qed_stop_rxq_params rx_params;


		for (tc = 0; tc < edev->num_tc; tc++) {
			struct qed_stop_txq_params tx_params;

			tx_params.rss_id = i;
			tx_params.tx_queue_id = tc * QEDE_RSS_CNT(edev) + i;
			rc = edev->ops->q_tx_stop(cdev, &tx_params);
			if (rc) {
				DP_ERR(edev, "Failed to stop TXQ #%d\n",
				       tx_params.tx_queue_id);
				return rc;
			}
		}


		memset(&rx_params, 0, sizeof(rx_params));
		rx_params.rss_id = i;
		rx_params.rx_queue_id = i;

		rc = edev->ops->q_rx_stop(cdev, &rx_params);
		if (rc) {
			DP_ERR(edev, "Failed to stop RXQ #%d\n", i);
			return rc;
		}
	}


	rc = edev->ops->vport_stop(cdev, 0);
	if (rc)
		DP_ERR(edev, "Failed to stop VPORT\n");

	return rc;
}
