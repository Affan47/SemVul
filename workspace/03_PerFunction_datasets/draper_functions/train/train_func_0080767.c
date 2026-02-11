qed_configure_filter_rx_mode(struct qed_dev *cdev,
					enum qed_filter_rx_mode_type type)
{
	struct qed_filter_accept_flags accept_flags;

	memset(&accept_flags, 0, sizeof(accept_flags));

	accept_flags.update_rx_mode_config	= 1;
	accept_flags.update_tx_mode_config	= 1;
	accept_flags.rx_accept_filter		= QED_ACCEPT_UCAST_MATCHED |
						  QED_ACCEPT_MCAST_MATCHED |
						  QED_ACCEPT_BCAST;
	accept_flags.tx_accept_filter = QED_ACCEPT_UCAST_MATCHED |
					QED_ACCEPT_MCAST_MATCHED |
					QED_ACCEPT_BCAST;

	if (type == QED_FILTER_RX_MODE_TYPE_PROMISC)
		accept_flags.rx_accept_filter |= QED_ACCEPT_UCAST_UNMATCHED |
						 QED_ACCEPT_MCAST_UNMATCHED;
	else if (type == QED_FILTER_RX_MODE_TYPE_MULTI_PROMISC)
		accept_flags.rx_accept_filter |= QED_ACCEPT_MCAST_UNMATCHED;

	return qed_filter_accept_cmd(cdev, 0, accept_flags,
				     QED_SPQ_MODE_CB, NULL);
}
