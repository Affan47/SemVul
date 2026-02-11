e1000e_cfg_kmrn_1000_80003es2lan(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;
	u16 reg_data, reg_data2;
	u32 tipg;
	u32 i = 0;

	reg_data = E1000_KMRNCTRLSTA_HD_CTRL_1000_DEFAULT;
	ret_val = e1000e_write_kmrn_reg_80003es2lan(hw,
	                               E1000_KMRNCTRLSTA_OFFSET_HD_CTRL,
	                               reg_data);
	if (ret_val)
		goto out;


	tipg = er32(TIPG);
	tipg &= ~E1000_TIPG_IPGT_MASK;
	tipg |= DEFAULT_TIPG_IPGT_1000_80003ES2LAN;
	ew32(TIPG, tipg);


	do {
		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL,
		                               &reg_data);
		if (ret_val)
			goto out;

		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL,
		                               &reg_data2);
		if (ret_val)
			goto out;
		i++;
	} while ((reg_data != reg_data2) && (i < GG82563_MAX_KMRN_RETRY));

	reg_data &= ~GG82563_KMCR_PASS_FALSE_CARRIER;
	ret_val = e1e_wphy(hw, GG82563_PHY_KMRN_MODE_CTRL, reg_data);

out:
	return ret_val;
}
