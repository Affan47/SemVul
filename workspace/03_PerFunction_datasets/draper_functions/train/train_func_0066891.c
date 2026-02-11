bnx2_nvram_read_dword(struct bnx2 *bp, u32 offset, u8 *ret_val, u32 cmd_flags)
{
	u32 cmd;
	int j;


	cmd = BNX2_NVM_COMMAND_DOIT | cmd_flags;


	if (bp->flash_info->flags & BNX2_NV_TRANSLATE) {
		offset = ((offset / bp->flash_info->page_size) <<
			   bp->flash_info->page_bits) +
			  (offset % bp->flash_info->page_size);
	}


	BNX2_WR(bp, BNX2_NVM_COMMAND, BNX2_NVM_COMMAND_DONE);


	BNX2_WR(bp, BNX2_NVM_ADDR, offset & BNX2_NVM_ADDR_NVM_ADDR_VALUE);


	BNX2_WR(bp, BNX2_NVM_COMMAND, cmd);


	for (j = 0; j < NVRAM_TIMEOUT_COUNT; j++) {
		u32 val;

		udelay(5);

		val = BNX2_RD(bp, BNX2_NVM_COMMAND);
		if (val & BNX2_NVM_COMMAND_DONE) {
			__be32 v = cpu_to_be32(BNX2_RD(bp, BNX2_NVM_READ));
			memcpy(ret_val, &v, 4);
			break;
		}
	}
	if (j >= NVRAM_TIMEOUT_COUNT)
		return -EBUSY;

	return 0;
}
