mptscsih_bus_reset(struct scsi_cmnd * SCpnt)
{
	MPT_SCSI_HOST	*hd;
	int		 retval;
	VirtDevice	 *vdevice;
	MPT_ADAPTER	*ioc;


	if ((hd = shost_priv(SCpnt->device->host)) == NULL){
		printk(KERN_ERR MYNAM ": bus reset: "
		   "Can't locate host! (sc=%p)\n", SCpnt);
		return FAILED;
	}

	ioc = hd->ioc;
	printk(MYIOC_s_INFO_FMT "attempting bus reset! (sc=%p)\n",
	       ioc->name, SCpnt);
	scsi_print_command(SCpnt);

	if (ioc->timeouts < -1)
		ioc->timeouts++;

	vdevice = SCpnt->device->hostdata;
	if (!vdevice || !vdevice->vtarget)
		return SUCCESS;
	retval = mptscsih_IssueTaskMgmt(hd,
					MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS,
					vdevice->vtarget->channel, 0, 0, 0,
					mptscsih_get_tm_timeout(ioc));

	printk(MYIOC_s_INFO_FMT "bus reset: %s (sc=%p)\n",
	    ioc->name, ((retval == 0) ? "SUCCESS" : "FAILED" ), SCpnt);

	if (retval == 0)
		return SUCCESS;
	else
		return FAILED;
}
