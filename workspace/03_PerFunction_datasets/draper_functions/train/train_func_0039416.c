mt7601u_mac_work(struct work_struct *work)
{
	struct mt7601u_dev *dev = container_of(work, struct mt7601u_dev,
					       mac_work.work);
	struct {
		u32 addr_base;
		u32 span;
		u64 *stat_base;
	} spans[] = {
		{ MT_RX_STA_CNT0,	3,	dev->stats.rx_stat },
		{ MT_TX_STA_CNT0,	3,	dev->stats.tx_stat },
		{ MT_TX_AGG_STAT,	1,	dev->stats.aggr_stat },
		{ MT_MPDU_DENSITY_CNT,	1,	dev->stats.zero_len_del },
		{ MT_TX_AGG_CNT_BASE0,	8,	&dev->stats.aggr_n[0] },
		{ MT_TX_AGG_CNT_BASE1,	8,	&dev->stats.aggr_n[16] },
	};
	u32 sum, n;
	int i, j, k;


	k = 0;
	n = 0;
	sum = 0;
	for (i = 0; i < ARRAY_SIZE(spans); i++)
		for (j = 0; j < spans[i].span; j++) {
			u32 val = mt7601u_rr(dev, spans[i].addr_base + j * 4);

			spans[i].stat_base[j * 2] += val & 0xffff;
			spans[i].stat_base[j * 2 + 1] += val >> 16;


			if (spans[i].addr_base != MT_TX_AGG_CNT_BASE0 &&
			    spans[i].addr_base != MT_TX_AGG_CNT_BASE1)
				continue;

			n += (val >> 16) + (val & 0xffff);
			sum += (val & 0xffff) * (1 + k * 2) +
				(val >> 16) * (2 + k * 2);
			k++;
		}

	atomic_set(&dev->avg_ampdu_len, n ? DIV_ROUND_CLOSEST(sum, n) : 1);

	mt7601u_check_mac_err(dev);

	ieee80211_queue_delayed_work(dev->hw, &dev->mac_work, 10 * HZ);
}
