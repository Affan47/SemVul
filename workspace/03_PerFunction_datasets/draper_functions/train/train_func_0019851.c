rinoo_task_driver_destroy(t_sched *sched)
{
	XASSERTN(sched != NULL);

	rbtree_flush(&sched->driver.proc_tree);
}
