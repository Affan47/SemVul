ks_read_config(struct ks_net *ks)
{
	u16 reg_data = 0;


	reg_data = ks_rdreg8(ks, KS_CCR) & 0x00FF;
	reg_data |= ks_rdreg8(ks, KS_CCR+1) << 8;


	ks->sharedbus = (reg_data & CCR_SHARED) == CCR_SHARED;


	if (reg_data & CCR_8BIT) {
		ks->bus_width = ENUM_BUS_8BIT;
		ks->extra_byte = 1;
	} else if (reg_data & CCR_16BIT) {
		ks->bus_width = ENUM_BUS_16BIT;
		ks->extra_byte = 2;
	} else {
		ks->bus_width = ENUM_BUS_32BIT;
		ks->extra_byte = 4;
	}
}
