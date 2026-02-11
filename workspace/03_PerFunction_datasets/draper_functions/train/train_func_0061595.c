lpfc_debugfs_slow_ring_trc_open(struct inode *inode, struct file *file)
{
	struct lpfc_hba *phba = inode->i_private;
	struct lpfc_debug *debug;
	int size;
	int rc = -ENOMEM;

	if (!lpfc_debugfs_max_slow_ring_trc) {
		 rc = -ENOSPC;
		goto out;
	}

	debug = kmalloc(sizeof(*debug), GFP_KERNEL);
	if (!debug)
		goto out;


	size =  (lpfc_debugfs_max_slow_ring_trc * LPFC_DEBUG_TRC_ENTRY_SIZE);
	size = PAGE_ALIGN(size);

	debug->buffer = kmalloc(size, GFP_KERNEL);
	if (!debug->buffer) {
		kfree(debug);
		goto out;
	}

	debug->len = lpfc_debugfs_slow_ring_trc_data(phba, debug->buffer, size);
	file->private_data = debug;

	rc = 0;
out:
	return rc;
}
