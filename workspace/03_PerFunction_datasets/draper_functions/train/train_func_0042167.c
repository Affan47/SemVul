atl1c_tpd_avail(struct atl1c_adapter *adapter, enum atl1c_trans_queue type)
{
	struct atl1c_tpd_ring *tpd_ring = &adapter->tpd_ring[type];
	u16 next_to_use = 0;
	u16 next_to_clean = 0;

	next_to_clean = atomic_read(&tpd_ring->next_to_clean);
	next_to_use   = tpd_ring->next_to_use;

	return (u16)(next_to_clean > next_to_use) ?
		(next_to_clean - next_to_use - 1) :
		(tpd_ring->count + next_to_clean - next_to_use - 1);
}
