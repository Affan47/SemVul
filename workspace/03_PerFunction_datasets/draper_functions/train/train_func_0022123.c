mmc_all_send_cid(struct mmc_host *host, u32 *cid)
{
	int err;
	struct mmc_command cmd = {0};

	BUG_ON(!host);
	BUG_ON(!cid);

	cmd.opcode = MMC_ALL_SEND_CID;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_R2 | MMC_CMD_BCR;

	err = mmc_wait_for_cmd(host, &cmd, MMC_CMD_RETRIES);
	if (err)
		return err;

	memcpy(cid, cmd.resp, sizeof(u32) * 4);

	return 0;
}
