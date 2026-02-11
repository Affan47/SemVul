ipath_free_all_qps(struct ipath_qp_table *qpt)
{
	unsigned long flags;
	struct ipath_qp *qp;
	u32 n, qp_inuse = 0;

	spin_lock_irqsave(&qpt->lock, flags);
	for (n = 0; n < qpt->max; n++) {
		qp = qpt->table[n];
		qpt->table[n] = NULL;

		for (; qp; qp = qp->next)
			qp_inuse++;
	}
	spin_unlock_irqrestore(&qpt->lock, flags);

	for (n = 0; n < ARRAY_SIZE(qpt->map); n++)
		if (qpt->map[n].page)
			free_page((unsigned long) qpt->map[n].page);
	return qp_inuse;
}
