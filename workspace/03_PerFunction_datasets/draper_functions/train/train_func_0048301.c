vub300_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct vub300_mmc_host *vub300 = mmc_priv(mmc);
	if (!vub300->interface)
		return;
	kref_get(&vub300->kref);
	if (enable) {
		mutex_lock(&vub300->irq_mutex);
		if (vub300->irqs_queued) {
			vub300->irqs_queued -= 1;
			mmc_signal_sdio_irq(vub300->mmc);
		} else if (vub300->irq_disabled) {
			vub300->irq_disabled = 0;
			vub300->irq_enabled = 1;
			vub300_queue_poll_work(vub300, 0);
		} else if (vub300->irq_enabled) {

		} else {
			vub300->irq_enabled = 1;
			vub300_queue_poll_work(vub300, 0);
		}
		mutex_unlock(&vub300->irq_mutex);
	} else {
		vub300->irq_enabled = 0;
	}
	kref_put(&vub300->kref, vub300_delete);
}
