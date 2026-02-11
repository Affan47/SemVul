tonga_copy_bytes_to_smc(struct pp_smumgr *smumgr,
		uint32_t smcStartAddress, const uint8_t *src,
		uint32_t byteCount, uint32_t limit)
{
	uint32_t addr;
	uint32_t data, orig_data;
	int result = 0;
	uint32_t extra_shift;

	if (smumgr == NULL || smumgr->device == NULL)
		return -EINVAL;
	PP_ASSERT_WITH_CODE((0 == (3 & smcStartAddress)),
		"SMC address must be 4 byte aligned.",
		return 0;);

	PP_ASSERT_WITH_CODE((limit > (smcStartAddress + byteCount)),
		"SMC address is beyond the SMC RAM area.",
		return 0;);

	addr = smcStartAddress;

	while (byteCount >= 4) {


		data = (src[0] << 24) + (src[1] << 16) + (src[2] << 8) + src[3];

		result = tonga_set_smc_sram_address(smumgr, addr, limit);

		if (result)
			goto out;

		cgs_write_register(smumgr->device, mmSMC_IND_DATA_0, data);

		src += 4;
		byteCount -= 4;
		addr += 4;
	}

	if (0 != byteCount) {

		data = 0;

		result = tonga_set_smc_sram_address(smumgr, addr, limit);
		if (result)
			goto out;

		orig_data = cgs_read_register(smumgr->device,
							mmSMC_IND_DATA_0);
		extra_shift = 8 * (4 - byteCount);

		while (byteCount > 0) {
			data = (data << 8) + *src++;
			byteCount--;
		}

		data <<= extra_shift;
		data |= (orig_data & ~((~0UL) << extra_shift));

		result = tonga_set_smc_sram_address(smumgr, addr, limit);
		if (result)
			goto out;

		cgs_write_register(smumgr->device, mmSMC_IND_DATA_0, data);
	}

out:
	return result;
}
