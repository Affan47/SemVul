cw1200_register_bh(struct cw1200_common *priv)
{
	int err = 0;

	priv->bh_workqueue = alloc_workqueue("cw1200_bh",
				WQ_MEM_RECLAIM | WQ_HIGHPRI
				| WQ_CPU_INTENSIVE, 1);

	if (!priv->bh_workqueue)
		return -ENOMEM;

	INIT_WORK(&priv->bh_work, cw1200_bh_work);

	pr_debug("[BH] register.\n");

	atomic_set(&priv->bh_rx, 0);
	atomic_set(&priv->bh_tx, 0);
	atomic_set(&priv->bh_term, 0);
	atomic_set(&priv->bh_suspend, CW1200_BH_RESUMED);
	priv->bh_error = 0;
	priv->hw_bufs_used = 0;
	priv->buf_id_tx = 0;
	priv->buf_id_rx = 0;
	init_waitqueue_head(&priv->bh_wq);
	init_waitqueue_head(&priv->bh_evt_wq);

	err = !queue_work(priv->bh_workqueue, &priv->bh_work);
	WARN_ON(err);
	return err;
}
