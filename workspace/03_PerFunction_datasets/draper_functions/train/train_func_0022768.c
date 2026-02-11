qede_get_ethtool_stats(struct net_device *dev,
				   struct ethtool_stats *stats, u64 *buf)
{
	struct qede_dev *edev = netdev_priv(dev);
	int sidx, cnt = 0;
	int qid;

	qede_fill_by_demand_stats(edev);

	mutex_lock(&edev->qede_lock);

	for (sidx = 0; sidx < QEDE_NUM_STATS; sidx++)
		buf[cnt++] = QEDE_STATS_DATA(edev, sidx);

	for (sidx = 0; sidx < QEDE_NUM_RQSTATS; sidx++) {
		buf[cnt] = 0;
		for (qid = 0; qid < edev->num_rss; qid++)
			buf[cnt] += QEDE_RQSTATS_DATA(edev, sidx, qid);
		cnt++;
	}

	mutex_unlock(&edev->qede_lock);
}
