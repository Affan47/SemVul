vfree(const void *addr)
{
	BUG_ON(in_nmi());

	kmemleak_free(addr);

	if (!addr)
		return;
	if (unlikely(in_interrupt())) {
		struct vfree_deferred *p = this_cpu_ptr(&vfree_deferred);
		if (llist_add((struct llist_node *)addr, &p->list))
			schedule_work(&p->wq);
	} else
		__vunmap(addr, 1);
}
