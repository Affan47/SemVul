_aac_probe_container(struct scsi_cmnd * scsicmd, int (*callback)(struct scsi_cmnd *))
{
	struct fib * fibptr;
	int status = -ENOMEM;

	if ((fibptr = aac_fib_alloc((struct aac_dev *)scsicmd->device->host->hostdata))) {
		struct aac_query_mount *dinfo;

		aac_fib_init(fibptr);

		dinfo = (struct aac_query_mount *)fib_data(fibptr);

		if (fibptr->dev->supplement_adapter_info.SupportedOptions2 &
		    AAC_OPTION_VARIABLE_BLOCK_SIZE)
			dinfo->command = cpu_to_le32(VM_NameServeAllBlk);
		else
			dinfo->command = cpu_to_le32(VM_NameServe);

		dinfo->count = cpu_to_le32(scmd_id(scsicmd));
		dinfo->type = cpu_to_le32(FT_FILESYS);
		scsicmd->SCp.ptr = (char *)callback;

		status = aac_fib_send(ContainerCommand,
			  fibptr,
			  sizeof(struct aac_query_mount),
			  FsaNormal,
			  0, 1,
			  _aac_probe_container1,
			  (void *) scsicmd);


		if (status == -EINPROGRESS) {
			scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;
			return 0;
		}
		if (status < 0) {
			scsicmd->SCp.ptr = NULL;
			aac_fib_complete(fibptr);
			aac_fib_free(fibptr);
		}
	}
	if (status < 0) {
		struct fsa_dev_info *fsa_dev_ptr = ((struct aac_dev *)(scsicmd->device->host->hostdata))->fsa_dev;
		if (fsa_dev_ptr) {
			fsa_dev_ptr += scmd_id(scsicmd);
			if ((fsa_dev_ptr->valid & 1) == 0) {
				fsa_dev_ptr->valid = 0;
				return (*callback)(scsicmd);
			}
		}
	}
	return status;
}
