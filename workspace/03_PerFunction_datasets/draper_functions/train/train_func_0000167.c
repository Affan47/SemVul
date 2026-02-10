vmpressure_work_fn(struct work_struct *work)
{
	struct vmpressure *vmpr = work_to_vmpressure(work);
	unsigned long scanned;
	unsigned long reclaimed;

	spin_lock(&vmpr->sr_lock);


	scanned = vmpr->scanned;
	if (!scanned) {
		spin_unlock(&vmpr->sr_lock);
		return;
	}

	reclaimed = vmpr->reclaimed;
	vmpr->scanned = 0;
	vmpr->reclaimed = 0;
	spin_unlock(&vmpr->sr_lock);

	do {
		if (vmpressure_event(vmpr, scanned, reclaimed))
			break;


	} while ((vmpr = vmpressure_parent(vmpr)));
}
