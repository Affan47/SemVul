bnx2_test_intr(struct bnx2 *bp)
{
	int i;
	u16 status_idx;

	if (!netif_running(bp->dev))
		return -ENODEV;

	status_idx = BNX2_RD(bp, BNX2_PCICFG_INT_ACK_CMD) & 0xffff;


	BNX2_WR(bp, BNX2_HC_COMMAND, bp->hc_cmd | BNX2_HC_COMMAND_COAL_NOW);
	BNX2_RD(bp, BNX2_HC_COMMAND);

	for (i = 0; i < 10; i++) {
		if ((BNX2_RD(bp, BNX2_PCICFG_INT_ACK_CMD) & 0xffff) !=
			status_idx) {

			break;
		}

		msleep_interruptible(10);
	}
	if (i < 10)
		return 0;

	return -ENODEV;
}
