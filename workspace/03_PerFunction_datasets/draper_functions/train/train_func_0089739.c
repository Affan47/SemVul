vmw_cmdbuf_man_destroy(struct vmw_cmdbuf_man *man)
{
	WARN_ON_ONCE(man->has_pool);
	(void) vmw_cmdbuf_idle(man, false, 10*HZ);
	if (vmw_cmdbuf_startstop(man, false))
		DRM_ERROR("Failed stopping command buffer context 0.\n");

	vmw_generic_waiter_remove(man->dev_priv, SVGA_IRQFLAG_ERROR,
				  &man->dev_priv->error_waiters);
	tasklet_kill(&man->tasklet);
	(void) cancel_work_sync(&man->work);
	dma_pool_destroy(man->dheaders);
	dma_pool_destroy(man->headers);
	mutex_destroy(&man->cur_mutex);
	mutex_destroy(&man->space_mutex);
	kfree(man);
}
