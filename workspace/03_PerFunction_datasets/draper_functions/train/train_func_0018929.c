find_userfault(
	struct userfaultfd_ctx *ctx)
{
	wait_queue_t *wq;
	struct userfaultfd_wait_queue *uwq;

	VM_BUG_ON(!spin_is_locked(&ctx->fault_pending_wqh.lock));

	uwq = NULL;
	if (!waitqueue_active(&ctx->fault_pending_wqh))
		goto out;

	wq = list_last_entry(&ctx->fault_pending_wqh.task_list,
			     typeof(*wq), task_list);
	uwq = container_of(wq, struct userfaultfd_wait_queue, wq);
out:
	return uwq;
}
