reg_pattern_test(struct e1000_adapter *adapter, u64 *data, int reg,
			     u32 mask, u32 write)
{
	struct e1000_hw *hw = &adapter->hw;
	static const u32 test[] = {
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF
	};
	u8 __iomem *address = hw->hw_addr + reg;
	u32 read;
	int i;

	for (i = 0; i < ARRAY_SIZE(test); i++) {
		writel(write & test[i], address);
		read = readl(address);
		if (read != (write & test[i] & mask)) {
			e_err(drv, "pattern test reg %04X failed: "
			      "got 0x%08X expected 0x%08X\n",
			      reg, read, (write & test[i] & mask));
			*data = reg;
			return true;
		}
	}
	return false;
}
