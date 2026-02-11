aac_probe_container_callback2(struct scsi_cmnd * scsicmd)
{
	struct fsa_dev_info *fsa_dev_ptr = ((struct aac_dev *)(scsicmd->device->host->hostdata))->fsa_dev;

	if ((fsa_dev_ptr[scmd_id(scsicmd)].valid & 1))
		return aac_scsi_cmd(scsicmd);

	scsicmd->result = DID_NO_CONNECT << 16;
	scsicmd->scsi_done(scsicmd);
	return 0;
}
