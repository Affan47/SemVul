ccp_free_ksb(struct ccp_device *ccp, unsigned int start,
			 unsigned int count)
{
	if (!start)
		return;

	mutex_lock(&ccp->ksb_mutex);

	bitmap_clear(ccp->ksb, start - KSB_START, count);

	ccp->ksb_avail = 1;

	mutex_unlock(&ccp->ksb_mutex);

	wake_up_interruptible_all(&ccp->ksb_queue);
}
