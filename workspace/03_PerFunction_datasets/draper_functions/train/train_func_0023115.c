fimc_stop_capture(struct fimc_dev *fimc, bool suspend)
{
	unsigned long flags;

	if (!fimc_capture_active(fimc))
		return 0;

	spin_lock_irqsave(&fimc->slock, flags);
	set_bit(ST_CAPT_SHUT, &fimc->state);
	fimc_deactivate_capture(fimc);
	spin_unlock_irqrestore(&fimc->slock, flags);

	wait_event_timeout(fimc->irq_queue,
			   !test_bit(ST_CAPT_SHUT, &fimc->state),
			   (2*HZ/10));

	return fimc_capture_state_cleanup(fimc, suspend);
}
