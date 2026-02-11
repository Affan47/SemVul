mon_reader_add(struct mon_bus *mbus, struct mon_reader *r)
{
	unsigned long flags;
	struct list_head *p;

	spin_lock_irqsave(&mbus->lock, flags);
	if (mbus->nreaders == 0) {
		if (mbus == &mon_bus0) {
			list_for_each (p, &mon_buses) {
				struct mon_bus *m1;
				m1 = list_entry(p, struct mon_bus, bus_link);
				m1->u_bus->monitored = 1;
			}
		} else {
			mbus->u_bus->monitored = 1;
		}
	}
	mbus->nreaders++;
	list_add_tail(&r->r_link, &mbus->r_list);
	spin_unlock_irqrestore(&mbus->lock, flags);

	kref_get(&mbus->ref);
}
