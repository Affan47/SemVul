tg3_enable_ints(struct tg3 *tp)
{	DBGP("%s\n", __func__);

	tw32(TG3PCI_MISC_HOST_CTRL,
	     (tp->misc_host_ctrl & ~MISC_HOST_CTRL_MASK_PCI_INT));

	tp->coal_now = tp->coalesce_mode | HOSTCC_MODE_ENABLE;

	tw32_mailbox_f(tp->int_mbox, tp->last_tag << 24);


	if (!tg3_flag(tp, TAGGED_STATUS) &&
	    (tp->hw_status->status & SD_STATUS_UPDATED))
		tw32(GRC_LOCAL_CTRL, tp->grc_local_ctrl | GRC_LCLCTRL_SETINT);
	else
		tw32(HOSTCC_MODE, tp->coal_now);
}
