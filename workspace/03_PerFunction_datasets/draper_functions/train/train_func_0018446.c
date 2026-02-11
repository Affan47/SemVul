gigaset_get_cs_by_id(int id)
{
	unsigned long flags;
	struct cardstate *ret = NULL;
	struct cardstate *cs;
	struct gigaset_driver *drv;
	unsigned i;

	spin_lock_irqsave(&driver_lock, flags);
	list_for_each_entry(drv, &drivers, list) {
		spin_lock(&drv->lock);
		for (i = 0; i < drv->minors; ++i) {
			cs = drv->cs + i;
			if ((cs->flags & VALID_ID) && cs->myid == id) {
				ret = cs;
				break;
			}
		}
		spin_unlock(&drv->lock);
		if (ret)
			break;
	}
	spin_unlock_irqrestore(&driver_lock, flags);
	return ret;
}
