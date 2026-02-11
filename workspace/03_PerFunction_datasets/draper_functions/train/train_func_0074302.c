ahc_linux_queue_lck(struct scsi_cmnd * cmd, void (*scsi_done) (struct scsi_cmnd *))
{
	struct	 ahc_softc *ahc;
	struct	 ahc_linux_device *dev = scsi_transport_device_data(cmd->device);
	int rtn = SCSI_MLQUEUE_HOST_BUSY;
	unsigned long flags;

	ahc = *(struct ahc_softc **)cmd->device->host->hostdata;

	ahc_lock(ahc, &flags);
	if (ahc->platform_data->qfrozen == 0) {
		cmd->scsi_done = scsi_done;
		cmd->result = CAM_REQ_INPROG << 16;
		rtn = ahc_linux_run_command(ahc, dev, cmd);
	}
	ahc_unlock(ahc, &flags);

	return rtn;
}
