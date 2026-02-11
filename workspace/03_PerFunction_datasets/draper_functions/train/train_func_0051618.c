camel_msgport_destroy (CamelMsgPort *msgport)
{
	g_return_if_fail (msgport != NULL);

	if (msgport->pipe[0] >= 0) {
		MP_CLOSE (msgport->pipe[0]);
		MP_CLOSE (msgport->pipe[1]);
	}
	if (msgport->prpipe[0] != NULL) {
		PR_Close (msgport->prpipe[0]);
		PR_Close (msgport->prpipe[1]);
	}

	g_async_queue_unref (msgport->queue);
	g_slice_free (CamelMsgPort, msgport);
}
