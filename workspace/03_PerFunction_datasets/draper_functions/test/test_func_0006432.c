lx_interrupt_handle_async_events(struct lx6464es *chip, u32 irqsrc,
					    int *r_freq_changed,
					    u64 *r_notified_in_pipe_mask,
					    u64 *r_notified_out_pipe_mask)
{
	int err;
	u32 stat[9];


	u64 orun_mask;
	u64 urun_mask;
	int eb_pending_out = (irqsrc & MASK_SYS_STATUS_EOBO) ? 1 : 0;
	int eb_pending_in  = (irqsrc & MASK_SYS_STATUS_EOBI) ? 1 : 0;

	*r_freq_changed = (irqsrc & MASK_SYS_STATUS_FREQ) ? 1 : 0;

	err = lx_dsp_read_async_events(chip, stat);
	if (err < 0)
		return err;

	if (eb_pending_in) {
		*r_notified_in_pipe_mask = ((u64)stat[3] << 32)
			+ stat[4];
		dev_dbg(chip->card->dev, "interrupt: EOBI pending %llx\n",
			    *r_notified_in_pipe_mask);
	}
	if (eb_pending_out) {
		*r_notified_out_pipe_mask = ((u64)stat[1] << 32)
			+ stat[2];
		dev_dbg(chip->card->dev, "interrupt: EOBO pending %llx\n",
			    *r_notified_out_pipe_mask);
	}

	orun_mask = ((u64)stat[7] << 32) + stat[8];
	urun_mask = ((u64)stat[5] << 32) + stat[6];


	return err;
}
