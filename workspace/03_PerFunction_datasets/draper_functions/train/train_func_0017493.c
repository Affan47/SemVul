sync_timeline_signal(struct sync_timeline *obj)
{
	unsigned long flags;
	LIST_HEAD(signaled_pts);
	struct sync_pt *pt, *next;

	trace_sync_timeline(obj);

	spin_lock_irqsave(&obj->child_list_lock, flags);

	list_for_each_entry_safe(pt, next, &obj->active_list_head,
				 active_list) {
		if (fence_is_signaled_locked(&pt->base))
			list_del_init(&pt->active_list);
	}

	spin_unlock_irqrestore(&obj->child_list_lock, flags);
}
