ocfs2_find_slot(struct ocfs2_super *osb)
{
	int status;
	int slot;
	struct ocfs2_slot_info *si;

	si = osb->slot_info;

	spin_lock(&osb->osb_lock);
	ocfs2_update_slot_info(si);


	slot = __ocfs2_node_num_to_slot(si, osb->node_num);
	if (slot < 0) {


		slot = __ocfs2_find_empty_slot(si, osb->preferred_slot);
		if (slot < 0) {
			spin_unlock(&osb->osb_lock);
			mlog(ML_ERROR, "no free slots available!\n");
			status = -EINVAL;
			goto bail;
		}
	} else
		printk(KERN_INFO "ocfs2: Slot %d on device (%s) was already "
		       "allocated to this node!\n", slot, osb->dev_str);

	ocfs2_set_slot(si, slot, osb->node_num);
	osb->slot_num = slot;
	spin_unlock(&osb->osb_lock);

	trace_ocfs2_find_slot(osb->slot_num);

	status = ocfs2_update_disk_slot(osb, si, osb->slot_num);
	if (status < 0)
		mlog_errno(status);

bail:
	return status;
}
