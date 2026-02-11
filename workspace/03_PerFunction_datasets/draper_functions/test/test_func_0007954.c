ena_rss_configure(struct ena_adapter *adapter)
{
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	int rc;


	if (!ena_dev->rss.tbl_log_size) {
		rc = ena_rss_init_default(adapter);
		if (rc && (rc != -EOPNOTSUPP)) {
			netif_err(adapter, ifup, adapter->netdev,
				  "Failed to init RSS rc: %d\n", rc);
			return rc;
		}
	}


	rc = ena_com_indirect_table_set(ena_dev);
	if (unlikely(rc && rc != -EOPNOTSUPP))
		return rc;


	rc = ena_com_set_hash_function(ena_dev);
	if (unlikely(rc && (rc != -EOPNOTSUPP)))
		return rc;


	rc = ena_com_set_hash_ctrl(ena_dev);
	if (unlikely(rc && (rc != -EOPNOTSUPP)))
		return rc;

	return 0;
}
