isd200_init_info(struct us_data *us)
{
	struct isd200_info *info;

	info = kzalloc(sizeof(struct isd200_info), GFP_KERNEL);
	if (!info)
		return ISD200_ERROR;

	info->id = kzalloc(ATA_ID_WORDS * 2, GFP_KERNEL);
	info->RegsBuf = kmalloc(sizeof(info->ATARegs), GFP_KERNEL);
	info->srb.sense_buffer = kmalloc(SCSI_SENSE_BUFFERSIZE, GFP_KERNEL);

	if (!info->id || !info->RegsBuf || !info->srb.sense_buffer) {
		isd200_free_info_ptrs(info);
		kfree(info);
		return ISD200_ERROR;
	}

	us->extra = info;
	us->extra_destructor = isd200_free_info_ptrs;

	return ISD200_GOOD;
}
