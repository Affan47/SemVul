igbvf_read_mac_addr_vf(struct e1000_hw *hw)
{
	int i;

	for (i = 0; i < ETH_ADDR_LEN; i++)
		hw->mac.addr[i] = hw->mac.perm_addr[i];

	return E1000_SUCCESS;
}
