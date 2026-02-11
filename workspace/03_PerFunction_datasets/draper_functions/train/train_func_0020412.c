mthca_free(struct mthca_alloc *alloc, u32 obj)
{
	unsigned long flags;

	obj &= alloc->max - 1;

	spin_lock_irqsave(&alloc->lock, flags);

	clear_bit(obj, alloc->table);
	alloc->last = min(alloc->last, obj);
	alloc->top = (alloc->top + alloc->max) & alloc->mask;

	spin_unlock_irqrestore(&alloc->lock, flags);
}
