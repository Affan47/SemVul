hfi1_free_devdata(struct hfi1_devdata *dd)
{
	unsigned long flags;

	spin_lock_irqsave(&hfi1_devs_lock, flags);
	idr_remove(&hfi1_unit_table, dd->unit);
	list_del(&dd->list);
	spin_unlock_irqrestore(&hfi1_devs_lock, flags);
	hfi1_dbg_ibdev_exit(&dd->verbs_dev);
	rcu_barrier();
	free_percpu(dd->int_counter);
	free_percpu(dd->rcv_limit);
	ib_dealloc_device(&dd->verbs_dev.ibdev);
}
