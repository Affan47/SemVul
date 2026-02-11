e1000_read_mac_addr_generic(struct e1000_hw *hw)
{
	u32 rar_high;
	u32 rar_low;
	u16 i;

	rar_high = er32(RAH(0));
	rar_low = er32(RAL(0));

	for (i = 0; i < E1000_RAL_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i] = (u8)(rar_low >> (i * 8));

	for (i = 0; i < E1000_RAH_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i + 4] = (u8)(rar_high >> (i * 8));

	for (i = 0; i < ETH_ALEN; i++)
		hw->mac.addr[i] = hw->mac.perm_addr[i];

	return 0;
}
