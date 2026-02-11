async_done_continue(struct aead_request *req, int err,
				       int (*cont)(struct aead_request *))
{
	if (!err)
		err = cont(req);

	if (err != -EINPROGRESS && err != -EBUSY)
		aead_request_complete(req, err);
}
