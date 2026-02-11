__v4l2_event_dequeue(struct v4l2_fh *fh, struct v4l2_event *event)
{
	struct v4l2_kevent *kev;
	unsigned long flags;

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);

	if (list_empty(&fh->available)) {
		spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
		return -ENOENT;
	}

	WARN_ON(fh->navailable == 0);

	kev = list_first_entry(&fh->available, struct v4l2_kevent, list);
	list_del(&kev->list);
	fh->navailable--;

	kev->event.pending = fh->navailable;
	*event = kev->event;
	kev->sev->first = sev_pos(kev->sev, 1);
	kev->sev->in_use--;

	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);

	return 0;
}
