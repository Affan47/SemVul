st33zp24_spi_recv(void *phy_id, u8 tpm_register, u8 *tpm_data,
			     int tpm_size)
{
	int ret;

	ret = read8_reg(phy_id, tpm_register, tpm_data, tpm_size);
	if (!st33zp24_status_to_errno(ret))
		return tpm_size;
	return ret;
}
