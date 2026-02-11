amd_ec_read(struct amd_smbus *smbus, unsigned char address,
		unsigned char *data)
{
	int status;

	status = amd_ec_wait_write(smbus);
	if (status)
		return status;
	outb(AMD_EC_CMD_RD, smbus->base + AMD_EC_CMD);

	status = amd_ec_wait_write(smbus);
	if (status)
		return status;
	outb(address, smbus->base + AMD_EC_DATA);

	status = amd_ec_wait_read(smbus);
	if (status)
		return status;
	*data = inb(smbus->base + AMD_EC_DATA);

	return 0;
}
