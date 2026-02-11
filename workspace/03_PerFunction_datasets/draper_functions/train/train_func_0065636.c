sdma_notify_taskbody(struct ipath_devdata *dd)
{
	unsigned long flags;
	struct list_head list;

	INIT_LIST_HEAD(&list);

	spin_lock_irqsave(&dd->ipath_sdma_lock, flags);

	list_splice_init(&dd->ipath_sdma_notifylist, &list);

	spin_unlock_irqrestore(&dd->ipath_sdma_lock, flags);

	ipath_sdma_notify(dd, &list);


	ipath_ib_piobufavail(dd->verbs_dev);
}
