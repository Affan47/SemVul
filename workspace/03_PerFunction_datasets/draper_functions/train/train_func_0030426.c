ixgbe_configure_virtualization(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 reg_offset, vf_shift;
	u32 gcr_ext, vmdctl;
	int i;

	if (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		return;

	vmdctl = IXGBE_READ_REG(hw, IXGBE_VT_CTL);
	vmdctl |= IXGBE_VMD_CTL_VMDQ_EN;
	vmdctl &= ~IXGBE_VT_CTL_POOL_MASK;
	vmdctl |= VMDQ_P(0) << IXGBE_VT_CTL_POOL_SHIFT;
	vmdctl |= IXGBE_VT_CTL_REPLEN;
	IXGBE_WRITE_REG(hw, IXGBE_VT_CTL, vmdctl);

	vf_shift = VMDQ_P(0) % 32;
	reg_offset = (VMDQ_P(0) >= 32) ? 1 : 0;


	IXGBE_WRITE_REG(hw, IXGBE_VFRE(reg_offset), (~0) << vf_shift);
	IXGBE_WRITE_REG(hw, IXGBE_VFRE(reg_offset ^ 1), reg_offset - 1);
	IXGBE_WRITE_REG(hw, IXGBE_VFTE(reg_offset), (~0) << vf_shift);
	IXGBE_WRITE_REG(hw, IXGBE_VFTE(reg_offset ^ 1), reg_offset - 1);
	if (adapter->bridge_mode == BRIDGE_MODE_VEB)
		IXGBE_WRITE_REG(hw, IXGBE_PFDTXGSWC, IXGBE_PFDTXGSWC_VT_LBEN);


	hw->mac.ops.set_vmdq(hw, 0, VMDQ_P(0));


	adapter->flags2 &= ~IXGBE_FLAG2_VLAN_PROMISC;


	switch (adapter->ring_feature[RING_F_VMDQ].mask) {
	case IXGBE_82599_VMDQ_8Q_MASK:
		gcr_ext = IXGBE_GCR_EXT_VT_MODE_16;
		break;
	case IXGBE_82599_VMDQ_4Q_MASK:
		gcr_ext = IXGBE_GCR_EXT_VT_MODE_32;
		break;
	default:
		gcr_ext = IXGBE_GCR_EXT_VT_MODE_64;
		break;
	}

	IXGBE_WRITE_REG(hw, IXGBE_GCR_EXT, gcr_ext);


	hw->mac.ops.set_mac_anti_spoofing(hw, (adapter->num_vfs != 0),
					  adapter->num_vfs);


	if (hw->mac.ops.set_ethertype_anti_spoofing) {
		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_LLDP),
				(IXGBE_ETQF_FILTER_EN    |
				 IXGBE_ETQF_TX_ANTISPOOF |
				 IXGBE_ETH_P_LLDP));

		IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_FC),
				(IXGBE_ETQF_FILTER_EN |
				 IXGBE_ETQF_TX_ANTISPOOF |
				 ETH_P_PAUSE));
	}


	for (i = 0; i < adapter->num_vfs; i++) {
		if (!adapter->vfinfo[i].spoofchk_enabled)
			ixgbe_ndo_set_vf_spoofchk(adapter->netdev, i, false);


		if (hw->mac.ops.set_ethertype_anti_spoofing)
			hw->mac.ops.set_ethertype_anti_spoofing(hw, true, i);


		ixgbe_ndo_set_vf_rss_query_en(adapter->netdev, i,
					  adapter->vfinfo[i].rss_query_enabled);
	}
}
