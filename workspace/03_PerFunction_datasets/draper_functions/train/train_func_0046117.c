iop_intr_mv(struct hptiop_hba *hba)
{
	u32 status;
	int ret = 0;

	status = readl(&hba->u.mv.regs->outbound_doorbell);
	writel(~status, &hba->u.mv.regs->outbound_doorbell);

	if (status & MVIOP_MU_OUTBOUND_INT_MSG) {
		u32 msg;
		msg = readl(&hba->u.mv.mu->outbound_msg);
		dprintk("received outbound msg %x\n", msg);
		hptiop_message_callback(hba, msg);
		ret = 1;
	}

	if (status & MVIOP_MU_OUTBOUND_INT_POSTQUEUE) {
		u64 tag;

		while ((tag = mv_outbound_read(hba->u.mv.mu)))
			hptiop_request_callback_mv(hba, tag);
		ret = 1;
	}

	return ret;
}
