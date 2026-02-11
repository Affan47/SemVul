qib_register_observer(struct qib_devdata *dd,
			  const struct diag_observer *op)
{
	struct diag_observer_list_elt *olp;
	unsigned long flags;

	if (!dd || !op)
		return -EINVAL;
	olp = vmalloc(sizeof(*olp));
	if (!olp) {
		pr_err("vmalloc for observer failed\n");
		return -ENOMEM;
	}

	spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
	olp->op = op;
	olp->next = dd->diag_observer_list;
	dd->diag_observer_list = olp;
	spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);

	return 0;
}
