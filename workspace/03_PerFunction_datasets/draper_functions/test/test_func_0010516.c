regmap_ipc_byte_reg_read(void *context, unsigned int reg,
				    unsigned int *val)
{
	int ret;
	int i2c_addr;
	u8 ipc_in[2];
	u8 ipc_out[4];
	struct intel_soc_pmic *pmic = context;

	if (reg & REG_ADDR_MASK)
		i2c_addr = (reg & REG_ADDR_MASK) >> REG_ADDR_SHIFT;
	else {
		i2c_addr = BXTWC_DEVICE1_ADDR;
		if (!i2c_addr) {
			dev_err(pmic->dev, "I2C address not set\n");
			return -EINVAL;
		}
	}
	reg &= REG_OFFSET_MASK;

	ipc_in[0] = reg;
	ipc_in[1] = i2c_addr;
	ret = intel_pmc_ipc_command(PMC_IPC_PMIC_ACCESS,
			PMC_IPC_PMIC_ACCESS_READ,
			ipc_in, sizeof(ipc_in), (u32 *)ipc_out, 1);
	if (ret) {
		dev_err(pmic->dev, "Failed to read from PMIC\n");
		return ret;
	}
	*val = ipc_out[0];

	return 0;
}
