findcontrbydriverid(int driverid)
{
	unsigned long flags;
	capidrv_contr *p;

	spin_lock_irqsave(&global_lock, flags);
	for (p = global.contr_list; p; p = p->next)
		if (p->myid == driverid)
			break;
	spin_unlock_irqrestore(&global_lock, flags);
	return p;
}
