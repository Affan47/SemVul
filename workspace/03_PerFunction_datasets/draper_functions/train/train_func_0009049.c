aoedev_put(struct aoedev *d)
{
	ulong flags;

	spin_lock_irqsave(&devlist_lock, flags);
	d->ref--;
	spin_unlock_irqrestore(&devlist_lock, flags);
}
