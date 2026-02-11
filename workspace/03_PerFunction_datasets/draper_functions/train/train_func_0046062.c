ixgbe_set_vf_vlan(struct ixgbe_adapter *adapter, int add, int vid,
			     u32 vf)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int err;


	if (add && test_bit(vid, adapter->active_vlans)) {
		err = hw->mac.ops.set_vfta(hw, vid, VMDQ_P(0), true, false);
		if (err)
			return err;
	}

	err = hw->mac.ops.set_vfta(hw, vid, vf, !!add, false);

	if (add && !err)
		return err;


	if (test_bit(vid, adapter->active_vlans) ||
	    (adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC))
		ixgbe_update_pf_promisc_vlvf(adapter, vid);

	return err;
}
