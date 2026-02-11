qlge_restore_vlan(struct ql_adapter *qdev)
{
	int status;
	u16 vid;

	status = ql_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	if (status)
		return;

	for_each_set_bit(vid, qdev->active_vlans, VLAN_N_VID)
		__qlge_vlan_rx_add_vid(qdev, vid);

	ql_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
}
