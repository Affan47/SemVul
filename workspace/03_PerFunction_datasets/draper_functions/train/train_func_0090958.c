forward_taskmgmt_command(enum task_mgmt_types tasktype,
				    struct scsi_cmnd *scsicmd)
{
	struct uiscmdrsp *cmdrsp;
	struct scsi_device *scsidev = scsicmd->device;
	struct visorhba_devdata *devdata =
		(struct visorhba_devdata *)scsidev->host->hostdata;
	int notifyresult = 0xffff;
	wait_queue_head_t notifyevent;
	int scsicmd_id = 0;

	if (devdata->serverdown || devdata->serverchangingstate)
		return FAILED;

	scsicmd_id = add_scsipending_entry(devdata, CMD_SCSITASKMGMT_TYPE,
					   NULL);
	if (scsicmd_id < 0)
		return FAILED;

	cmdrsp = get_scsipending_cmdrsp(devdata, scsicmd_id);

	init_waitqueue_head(&notifyevent);


	cmdrsp->cmdtype = CMD_SCSITASKMGMT_TYPE;


	cmdrsp->scsitaskmgmt.notify_handle = (u64)&notifyevent;
	cmdrsp->scsitaskmgmt.notifyresult_handle = (u64)&notifyresult;


	cmdrsp->scsitaskmgmt.tasktype = tasktype;
	cmdrsp->scsitaskmgmt.vdest.channel = scsidev->channel;
	cmdrsp->scsitaskmgmt.vdest.id = scsidev->id;
	cmdrsp->scsitaskmgmt.vdest.lun = scsidev->lun;
	cmdrsp->scsitaskmgmt.handle = scsicmd_id;

	if (!visorchannel_signalinsert(devdata->dev->visorchannel,
				       IOCHAN_TO_IOPART,
				       cmdrsp))
		goto err_del_scsipending_ent;


	if (!wait_event_timeout(notifyevent, notifyresult != 0xffff,
				msecs_to_jiffies(45000)))
		goto err_del_scsipending_ent;

	if (tasktype == TASK_MGMT_ABORT_TASK)
		scsicmd->result = (DID_ABORT << 16);
	else
		scsicmd->result = (DID_RESET << 16);

	scsicmd->scsi_done(scsicmd);

	return SUCCESS;

err_del_scsipending_ent:
	del_scsipending_ent(devdata, scsicmd_id);
	return FAILED;
}
