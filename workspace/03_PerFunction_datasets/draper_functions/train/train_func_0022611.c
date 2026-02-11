mvumi_check_handshake(struct mvumi_hba *mhba)
{
	unsigned int tmp;
	unsigned long before;

	before = jiffies;
	tmp = ioread32(mhba->regs->arm_to_pciea_msg1);
	while ((tmp != HANDSHAKE_READYSTATE) && (tmp != HANDSHAKE_DONESTATE)) {
		if (tmp != HANDSHAKE_READYSTATE)
			iowrite32(DRBL_MU_RESET,
					mhba->regs->pciea_to_arm_drbl_reg);
		if (time_after(jiffies, before + FW_MAX_DELAY * HZ)) {
			dev_err(&mhba->pdev->dev,
				"invalid signature [0x%x].\n", tmp);
			return -1;
		}
		usleep_range(1000, 2000);
		rmb();
		tmp = ioread32(mhba->regs->arm_to_pciea_msg1);
	}

	mhba->fw_state = FW_STATE_STARTING;
	dev_dbg(&mhba->pdev->dev, "start firmware handshake...\n");
	do {
		if (mvumi_handshake_event(mhba)) {
			dev_err(&mhba->pdev->dev,
					"handshake failed at state 0x%x.\n",
						mhba->fw_state);
			return -1;
		}
	} while (mhba->fw_state != FW_STATE_STARTED);

	dev_dbg(&mhba->pdev->dev, "firmware handshake done\n");

	return 0;
}
