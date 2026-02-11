c4iw_get_qpid(struct c4iw_rdev *rdev, struct c4iw_dev_ucontext *uctx)
{
	struct c4iw_qid_list *entry;
	u32 qid;
	int i;

	mutex_lock(&uctx->lock);
	if (!list_empty(&uctx->qpids)) {
		entry = list_entry(uctx->qpids.next, struct c4iw_qid_list,
				   entry);
		list_del(&entry->entry);
		qid = entry->qid;
		kfree(entry);
	} else {
		qid = c4iw_get_resource(&rdev->resource.qid_table);
		if (!qid) {
			mutex_lock(&rdev->stats.lock);
			rdev->stats.qid.fail++;
			mutex_unlock(&rdev->stats.lock);
			goto out;
		}
		mutex_lock(&rdev->stats.lock);
		rdev->stats.qid.cur += rdev->qpmask + 1;
		mutex_unlock(&rdev->stats.lock);
		for (i = qid+1; i & rdev->qpmask; i++) {
			entry = kmalloc(sizeof *entry, GFP_KERNEL);
			if (!entry)
				goto out;
			entry->qid = i;
			list_add_tail(&entry->entry, &uctx->qpids);
		}


		entry = kmalloc(sizeof *entry, GFP_KERNEL);
		if (!entry)
			goto out;
		entry->qid = qid;
		list_add_tail(&entry->entry, &uctx->cqids);
		for (i = qid; i & rdev->qpmask; i++) {
			entry = kmalloc(sizeof *entry, GFP_KERNEL);
			if (!entry)
				goto out;
			entry->qid = i;
			list_add_tail(&entry->entry, &uctx->cqids);
		}
	}
out:
	mutex_unlock(&uctx->lock);
	PDBG("%s qid 0x%x\n", __func__, qid);
	mutex_lock(&rdev->stats.lock);
	if (rdev->stats.qid.cur > rdev->stats.qid.max)
		rdev->stats.qid.max = rdev->stats.qid.cur;
	mutex_unlock(&rdev->stats.lock);
	return qid;
}
