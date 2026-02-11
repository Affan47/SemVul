hnae_reinit_handle(struct hnae_handle *handle)
{
	int i, j;
	int ret;

	for (i = 0; i < handle->q_num; i++)
		hnae_fini_queue(handle->qs[i]);

	if (handle->dev->ops->reset)
		handle->dev->ops->reset(handle);

	for (i = 0; i < handle->q_num; i++) {
		ret = hnae_init_queue(handle, handle->qs[i], handle->dev);
		if (ret)
			goto out_when_init_queue;
	}
	return 0;
out_when_init_queue:
	for (j = i - 1; j >= 0; j--)
		hnae_fini_queue(handle->qs[j]);
	return ret;
}
