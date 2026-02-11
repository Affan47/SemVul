camel_msgport_try_pop (CamelMsgPort *msgport)
{
	CamelMsg *msg;

	g_return_val_if_fail (msgport != NULL, NULL);

	g_async_queue_lock (msgport->queue);

	msg = g_async_queue_try_pop_unlocked (msgport->queue);

	if (msg != NULL && msg->flags & MSG_FLAG_SYNC_WITH_PIPE)
		msgport_sync_with_pipe (msgport->pipe[0]);
	if (msg != NULL && msg->flags & MSG_FLAG_SYNC_WITH_PR_PIPE)
		msgport_sync_with_prpipe (msgport->prpipe[0]);

	g_async_queue_unlock (msgport->queue);

	return msg;
}
