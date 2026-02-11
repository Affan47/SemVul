trash_mbo(struct mbo *mbo)
{
	unsigned long flags;
	struct most_c_obj *c = mbo->context;

	spin_lock_irqsave(&c->fifo_lock, flags);
	list_add(&mbo->list, &c->trash_fifo);
	spin_unlock_irqrestore(&c->fifo_lock, flags);
}
