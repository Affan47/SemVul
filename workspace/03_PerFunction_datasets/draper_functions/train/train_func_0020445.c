hfi1_count_active_units(void)
{
	struct hfi1_devdata *dd;
	struct hfi1_pportdata *ppd;
	unsigned long flags;
	int pidx, nunits_active = 0;

	spin_lock_irqsave(&hfi1_devs_lock, flags);
	list_for_each_entry(dd, &hfi1_dev_list, list) {
		if (!(dd->flags & HFI1_PRESENT) || !dd->kregbase)
			continue;
		for (pidx = 0; pidx < dd->num_pports; ++pidx) {
			ppd = dd->pport + pidx;
			if (ppd->lid && ppd->linkup) {
				nunits_active++;
				break;
			}
		}
	}
	spin_unlock_irqrestore(&hfi1_devs_lock, flags);
	return nunits_active;
}
