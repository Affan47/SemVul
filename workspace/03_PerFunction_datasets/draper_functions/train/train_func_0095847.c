e1000e_init_hw_80003es2lan(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 reg_data;
	s32 ret_val;
	u16 i;

	e1000e_initialize_hw_bits_80003es2lan(hw);


	ret_val = mac->ops.id_led_init(hw);
	if (ret_val) {
		e_dbg("Error initializing identification LED\n");

	}


	e_dbg("Initializing the IEEE VLAN\n");
	e1000e_clear_vfta(hw);


	e1000e_init_rx_addrs(hw, mac->rar_entry_count);


	e_dbg("Zeroing the MTA\n");
	for (i = 0; i < mac->mta_reg_count; i++)
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, 0);


	ret_val = mac->ops.setup_link(hw);


	reg_data = er32(TXDCTL(0));
	reg_data = (reg_data & ~E1000_TXDCTL_WTHRESH) |
	           E1000_TXDCTL_FULL_TX_DESC_WB | E1000_TXDCTL_COUNT_DESC;
	ew32(TXDCTL(0), reg_data);


	reg_data = er32(TXDCTL(1));
	reg_data = (reg_data & ~E1000_TXDCTL_WTHRESH) |
	           E1000_TXDCTL_FULL_TX_DESC_WB | E1000_TXDCTL_COUNT_DESC;
	ew32(TXDCTL(1), reg_data);


	reg_data = er32(TCTL);
	reg_data |= E1000_TCTL_RTLC;
	ew32(TCTL, reg_data);


	reg_data = er32(TCTL_EXT);
	reg_data &= ~E1000_TCTL_EXT_GCEX_MASK;
	reg_data |= DEFAULT_TCTL_EXT_GCEX_80003ES2LAN;
	ew32(TCTL_EXT, reg_data);


	reg_data = er32(TIPG);
	reg_data &= ~E1000_TIPG_IPGT_MASK;
	reg_data |= DEFAULT_TIPG_IPGT_1000_80003ES2LAN;
	ew32(TIPG, reg_data);

	reg_data = E1000_READ_REG_ARRAY(hw, E1000_FFLT, 0x0001);
	reg_data &= ~0x00100000;
	E1000_WRITE_REG_ARRAY(hw, E1000_FFLT, 0x0001, reg_data);


	hw->dev_spec._80003es2lan.mdic_wa_enable = true;

	ret_val = e1000e_read_kmrn_reg_80003es2lan(hw,
	                              E1000_KMRNCTRLSTA_OFFSET >>
	                              E1000_KMRNCTRLSTA_OFFSET_SHIFT,
	                              &i);
	if (!ret_val) {
		if ((i & E1000_KMRNCTRLSTA_OPMODE_MASK) ==
		     E1000_KMRNCTRLSTA_OPMODE_INBAND_MDIO)
			hw->dev_spec._80003es2lan.mdic_wa_enable = false;
	}


	e1000e_clear_hw_cntrs_80003es2lan(hw);

	return ret_val;
}
