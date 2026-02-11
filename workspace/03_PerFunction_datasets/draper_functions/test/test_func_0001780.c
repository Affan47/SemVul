mptsas_qcmd(struct Scsi_Host *shost, struct scsi_cmnd *SCpnt)
{
	MPT_SCSI_HOST	*hd;
	MPT_ADAPTER	*ioc;
	VirtDevice	*vdevice = SCpnt->device->hostdata;

	if (!vdevice || !vdevice->vtarget || vdevice->vtarget->deleted) {
		SCpnt->result = DID_NO_CONNECT << 16;
		SCpnt->scsi_done(SCpnt);
		return 0;
	}

	hd = shost_priv(shost);
	ioc = hd->ioc;

	if (ioc->sas_discovery_quiesce_io)
		return SCSI_MLQUEUE_HOST_BUSY;

	if (ioc->debug_level & MPT_DEBUG_SCSI)
		scsi_print_command(SCpnt);

	return mptscsih_qcmd(SCpnt);
}
