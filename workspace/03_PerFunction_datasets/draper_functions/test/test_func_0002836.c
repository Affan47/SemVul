wl1251_hw_init_txq_fill(u8 qid,
				   struct acx_tx_queue_qos_config *config,
				   u32 num_blocks)
{
	config->qid = qid;

	switch (qid) {
	case QOS_AC_BE:
		config->high_threshold =
			(QOS_TX_HIGH_BE_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_BE_DEF * num_blocks) / 100;
		break;
	case QOS_AC_BK:
		config->high_threshold =
			(QOS_TX_HIGH_BK_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_BK_DEF * num_blocks) / 100;
		break;
	case QOS_AC_VI:
		config->high_threshold =
			(QOS_TX_HIGH_VI_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_VI_DEF * num_blocks) / 100;
		break;
	case QOS_AC_VO:
		config->high_threshold =
			(QOS_TX_HIGH_VO_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_VO_DEF * num_blocks) / 100;
		break;
	default:
		wl1251_error("Invalid TX queue id: %d", qid);
		return -EINVAL;
	}

	return 0;
}
