crypt_dtr(struct dm_target *ti)
{
	struct crypt_config *cc = ti->private;

	ti->private = NULL;

	if (!cc)
		return;

	if (cc->write_thread)
		kthread_stop(cc->write_thread);

	if (cc->io_queue)
		destroy_workqueue(cc->io_queue);
	if (cc->crypt_queue)
		destroy_workqueue(cc->crypt_queue);

	crypt_free_tfms(cc);

	if (cc->bs)
		bioset_free(cc->bs);

	mempool_destroy(cc->page_pool);
	mempool_destroy(cc->req_pool);

	if (cc->iv_gen_ops && cc->iv_gen_ops->dtr)
		cc->iv_gen_ops->dtr(cc);

	if (cc->dev)
		dm_put_device(ti, cc->dev);

	kzfree(cc->cipher);
	kzfree(cc->cipher_string);


	kzfree(cc);
}
