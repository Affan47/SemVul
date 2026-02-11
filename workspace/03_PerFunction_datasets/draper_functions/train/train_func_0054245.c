scsi_debug_abort(struct scsi_cmnd *SCpnt)
{
	++num_aborts;
	if (SCpnt) {
		if (SCpnt->device &&
		    (SCSI_DEBUG_OPT_ALL_NOISE & scsi_debug_opts))
			sdev_printk(KERN_INFO, SCpnt->device, "%s\n",
				    __func__);
		stop_queued_cmnd(SCpnt);
	}
	return SUCCESS;
}
