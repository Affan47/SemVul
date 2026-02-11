bnx2_nvram_erase_page(struct bnx2 *bp, u32 offset)
{
	u32 cmd;
	int j;

	if (bp->flash_info->flags & BNX2_NV_BUFFERED)

		return 0;


	cmd = BNX2_NVM_COMMAND_ERASE | BNX2_NVM_COMMAND_WR |
	      BNX2_NVM_COMMAND_DOIT;


	BNX2_WR(bp, BNX2_NVM_COMMAND, BNX2_NVM_COMMAND_DONE);


	BNX2_WR(bp, BNX2_NVM_ADDR, offset & BNX2_NVM_ADDR_NVM_ADDR_VALUE);


	BNX2_WR(bp, BNX2_NVM_COMMAND, cmd);


	for (j = 0; j < NVRAM_TIMEOUT_COUNT; j++) {
		u32 val;

		udelay(5);

		val = BNX2_RD(bp, BNX2_NVM_COMMAND);
		if (val & BNX2_NVM_COMMAND_DONE)
			break;
	}

	if (j >= NVRAM_TIMEOUT_COUNT)
		return -EBUSY;

	return 0;
}
