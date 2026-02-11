cz_set_smc_sram_address(struct pp_smumgr *smumgr,
				     uint32_t smc_address, uint32_t limit)
{
	if (smumgr == NULL || smumgr->device == NULL)
		return -EINVAL;

	if (0 != (3 & smc_address)) {
		printk(KERN_ERR "[ powerplay ] SMC address must be 4 byte aligned\n");
		return -1;
	}

	if (limit <= (smc_address + 3)) {
		printk(KERN_ERR "[ powerplay ] SMC address beyond the SMC RAM area\n");
		return -1;
	}

	cgs_write_register(smumgr->device, mmMP0PUB_IND_INDEX_0,
				SMN_MP1_SRAM_START_ADDR + smc_address);

	return 0;
}
