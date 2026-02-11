__free_iova(struct iova_domain *iovad, struct iova *iova)
{
	unsigned long flags;

	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);
	__cached_rbnode_delete_update(iovad, iova);
	rb_erase(&iova->node, &iovad->rbroot);
	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);
	free_iova_mem(iova);
}
