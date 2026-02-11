qlcnic_max_rings(struct qlcnic_adapter *adapter, u8 ring_cnt,
			    int queue_type)
{
	int num_rings, max_rings = QLCNIC_MAX_SDS_RINGS;

	if (queue_type == QLCNIC_RX_QUEUE)
		max_rings = adapter->max_sds_rings;
	else if (queue_type == QLCNIC_TX_QUEUE)
		max_rings = adapter->max_tx_rings;

	num_rings = rounddown_pow_of_two(min_t(int, num_online_cpus(),
					      max_rings));

	if (ring_cnt > num_rings)
		return num_rings;
	else
		return ring_cnt;
}
