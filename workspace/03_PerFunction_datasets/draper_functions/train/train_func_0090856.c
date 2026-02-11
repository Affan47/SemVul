ccp_crypto_cmd_complete(
	struct ccp_crypto_cmd *crypto_cmd, struct ccp_crypto_cmd **backlog)
{
	struct ccp_crypto_cmd *held = NULL, *tmp;
	unsigned long flags;

	*backlog = NULL;

	spin_lock_irqsave(&req_queue_lock, flags);


	tmp = crypto_cmd;
	list_for_each_entry_continue(tmp, &req_queue.cmds, entry) {
		if (crypto_cmd->tfm != tmp->tfm)
			continue;
		held = tmp;
		break;
	}


	if (req_queue.backlog != &req_queue.cmds) {

		if (req_queue.backlog == &crypto_cmd->entry)
			req_queue.backlog = crypto_cmd->entry.next;

		*backlog = container_of(req_queue.backlog,
					struct ccp_crypto_cmd, entry);
		req_queue.backlog = req_queue.backlog->next;


		if (req_queue.backlog == &crypto_cmd->entry)
			req_queue.backlog = crypto_cmd->entry.next;
	}


	req_queue.cmd_count--;
	list_del(&crypto_cmd->entry);

	spin_unlock_irqrestore(&req_queue_lock, flags);

	return held;
}
