igb_read_mac_addr_82575(struct e1000_hw *hw)
{
	s32 ret_val = 0;


	ret_val = igb_check_alt_mac_addr(hw);
	if (ret_val)
		goto out;

	ret_val = igb_read_mac_addr(hw);

out:
	return ret_val;
}
