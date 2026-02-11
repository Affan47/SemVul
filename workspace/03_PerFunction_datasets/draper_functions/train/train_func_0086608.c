rhine_slow_event_task(struct work_struct *work)
{
	struct rhine_private *rp =
		container_of(work, struct rhine_private, slow_event_task);
	struct net_device *dev = rp->dev;
	u32 intr_status;

	mutex_lock(&rp->task_lock);

	if (!rp->task_enable)
		goto out_unlock;

	intr_status = rhine_get_events(rp);
	rhine_ack_events(rp, intr_status & RHINE_EVENT_SLOW);

	if (intr_status & IntrLinkChange)
		rhine_check_media(dev, 0);

	if (intr_status & IntrPCIErr)
		netif_warn(rp, hw, dev, "PCI error\n");

	iowrite16(RHINE_EVENT & 0xffff, rp->base + IntrEnable);

out_unlock:
	mutex_unlock(&rp->task_lock);
}
