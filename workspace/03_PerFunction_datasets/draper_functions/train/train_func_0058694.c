wait_for_tpm_stat(struct tpm_chip *chip, u8 mask, unsigned long timeout,
		      wait_queue_head_t *queue, bool check_cancel)
{
	unsigned long stop;
	long rc;
	u8 status;
	bool canceled = false;


	status = chip->ops->status(chip);
	if ((status & mask) == mask)
		return 0;

	stop = jiffies + timeout;

	if (chip->vendor.irq) {
again:
		timeout = stop - jiffies;
		if ((long)timeout <= 0)
			return -ETIME;
		rc = wait_event_interruptible_timeout(*queue,
			wait_for_tpm_stat_cond(chip, mask, check_cancel,
					       &canceled),
			timeout);
		if (rc > 0) {
			if (canceled)
				return -ECANCELED;
			return 0;
		}
		if (rc == -ERESTARTSYS && freezing(current)) {
			clear_thread_flag(TIF_SIGPENDING);
			goto again;
		}
	} else {
		do {
			msleep(TPM_TIMEOUT);
			status = chip->ops->status(chip);
			if ((status & mask) == mask)
				return 0;
		} while (time_before(jiffies, stop));
	}
	return -ETIME;
}
