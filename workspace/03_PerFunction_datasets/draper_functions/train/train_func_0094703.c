hw_read_addr(struct ksz_hw *hw)
{
	int i;

	for (i = 0; i < ETH_ALEN; i++)
		hw->perm_addr[MAC_ADDR_ORDER(i)] = readb(hw->io +
			KS884X_ADDR_0_OFFSET + i);

	if (!hw->mac_override) {
		memcpy(hw->override_addr, hw->perm_addr, ETH_ALEN);
		if (empty_addr(hw->override_addr)) {
			memcpy(hw->perm_addr, DEFAULT_MAC_ADDRESS, ETH_ALEN);
			memcpy(hw->override_addr, DEFAULT_MAC_ADDRESS,
			       ETH_ALEN);
			hw->override_addr[5] += hw->id;
			hw_set_addr(hw);
		}
	}
}
