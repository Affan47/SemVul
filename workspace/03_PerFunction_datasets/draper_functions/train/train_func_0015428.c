axi_clkgen_v2_mmcm_enable(struct axi_clkgen *axi_clkgen,
	bool enable)
{
	unsigned int val = AXI_CLKGEN_V2_RESET_ENABLE;

	if (enable)
		val |= AXI_CLKGEN_V2_RESET_MMCM_ENABLE;

	axi_clkgen_write(axi_clkgen, AXI_CLKGEN_V2_REG_RESET, val);
}
