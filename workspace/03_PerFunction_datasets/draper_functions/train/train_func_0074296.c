probe_tsb41ba3d(struct fw_ohci *ohci)
{

	static const u8 id[] = { 0x08, 0x00, 0x28, 0x83, 0x30, 0x05, };
	int reg, i;

	reg = read_phy_reg(ohci, 2);
	if (reg < 0)
		return reg;
	if ((reg & PHY_EXTENDED_REGISTERS) != PHY_EXTENDED_REGISTERS)
		return 0;

	for (i = ARRAY_SIZE(id) - 1; i >= 0; i--) {
		reg = read_paged_phy_reg(ohci, 1, i + 10);
		if (reg < 0)
			return reg;
		if (reg != id[i])
			return 0;
	}
	return 1;
}
