axi_clkgen_wait_non_busy(struct axi_clkgen *axi_clkgen)
{
	unsigned int timeout = 10000;
	unsigned int val;

	do {
		axi_clkgen_read(axi_clkgen, AXI_CLKGEN_V2_REG_DRP_STATUS, &val);
	} while ((val & AXI_CLKGEN_V2_DRP_STATUS_BUSY) && --timeout);

	if (val & AXI_CLKGEN_V2_DRP_STATUS_BUSY)
		return -EIO;

	return val & 0xffff;
}
