t3_mac_enable_exact_filters(struct cmac *mac)
{
	unsigned int i, reg = mac->offset + A_XGM_RX_EXACT_MATCH_HIGH_1;

	for (i = 0; i < EXACT_ADDR_FILTERS; i++, reg += 8) {
		u32 v = t3_read_reg(mac->adapter, reg);
		t3_write_reg(mac->adapter, reg, v);
	}
	t3_read_reg(mac->adapter, A_XGM_RX_EXACT_MATCH_LOW_1);
}
