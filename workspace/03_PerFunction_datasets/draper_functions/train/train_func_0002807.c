fm_irq_send_intmsk_cmd(struct fmdev *fmdev)
{
	u16 payload;


	payload = fmdev->irq_info.mask;

	if (!fm_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			sizeof(payload), NULL))
		fm_irq_timeout_stage(fmdev, FM_HANDLE_INTMSK_CMD_RESP_IDX);
}
