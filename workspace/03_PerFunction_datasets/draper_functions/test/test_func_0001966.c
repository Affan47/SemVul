hpsa_scsi_do_simple_cmd_core(struct ctlr_info *h,
	struct CommandList *c, int reply_queue, unsigned long timeout_msecs)
{
	DECLARE_COMPLETION_ONSTACK(wait);

	c->waiting = &wait;
	__enqueue_cmd_and_start_io(h, c, reply_queue);
	if (timeout_msecs == NO_TIMEOUT) {

		wait_for_completion_io(&wait);
		return IO_OK;
	}
	if (!wait_for_completion_io_timeout(&wait,
					msecs_to_jiffies(timeout_msecs))) {
		dev_warn(&h->pdev->dev, "Command timed out.\n");
		return -ETIMEDOUT;
	}
	return IO_OK;
}
