mpt_set_taskmgmt_in_progress_flag(MPT_ADAPTER *ioc)
{
	unsigned long	 flags;
	int		 retval;

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	if (ioc->ioc_reset_in_progress || ioc->taskmgmt_in_progress ||
	    (ioc->alt_ioc && ioc->alt_ioc->taskmgmt_in_progress)) {
		retval = -1;
		goto out;
	}
	retval = 0;
	ioc->taskmgmt_in_progress = 1;
	ioc->taskmgmt_quiesce_io = 1;
	if (ioc->alt_ioc) {
		ioc->alt_ioc->taskmgmt_in_progress = 1;
		ioc->alt_ioc->taskmgmt_quiesce_io = 1;
	}
 out:
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
	return retval;
}
