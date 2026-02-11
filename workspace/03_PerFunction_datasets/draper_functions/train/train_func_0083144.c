vmw_fence_work_func(struct work_struct *work)
{
	struct vmw_fence_manager *fman =
		container_of(work, struct vmw_fence_manager, work);
	struct list_head list;
	struct vmw_fence_action *action, *next_action;
	bool seqno_valid;

	do {
		INIT_LIST_HEAD(&list);
		mutex_lock(&fman->goal_irq_mutex);

		spin_lock_irq(&fman->lock);
		list_splice_init(&fman->cleanup_list, &list);
		seqno_valid = fman->seqno_valid;
		spin_unlock_irq(&fman->lock);

		if (!seqno_valid && fman->goal_irq_on) {
			fman->goal_irq_on = false;
			vmw_goal_waiter_remove(fman->dev_priv);
		}
		mutex_unlock(&fman->goal_irq_mutex);

		if (list_empty(&list))
			return;


		list_for_each_entry_safe(action, next_action, &list, head) {
			list_del_init(&action->head);
			if (action->cleanup)
				action->cleanup(action);
		}
	} while (1);
}
