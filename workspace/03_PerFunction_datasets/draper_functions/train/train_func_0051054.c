get_qpid(struct cxio_rdev *rdev_p, struct cxio_ucontext *uctx)
{
	struct cxio_qpid_list *entry;
	u32 qpid;
	int i;

	mutex_lock(&uctx->lock);
	if (!list_empty(&uctx->qpids)) {
		entry = list_entry(uctx->qpids.next, struct cxio_qpid_list,
				   entry);
		list_del(&entry->entry);
		qpid = entry->qpid;
		kfree(entry);
	} else {
		qpid = cxio_hal_get_qpid(rdev_p->rscp);
		if (!qpid)
			goto out;
		for (i = qpid+1; i & rdev_p->qpmask; i++) {
			entry = kmalloc(sizeof *entry, GFP_KERNEL);
			if (!entry)
				break;
			entry->qpid = i;
			list_add_tail(&entry->entry, &uctx->qpids);
		}
	}
out:
	mutex_unlock(&uctx->lock);
	PDBG("%s qpid 0x%x\n", __func__, qpid);
	return qpid;
}
