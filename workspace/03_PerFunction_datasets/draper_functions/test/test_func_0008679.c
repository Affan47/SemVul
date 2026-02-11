mptsas_target_reset_queue(MPT_ADAPTER *ioc,
    EVENT_DATA_SAS_DEVICE_STATUS_CHANGE *sas_event_data)
{
	MPT_SCSI_HOST	*hd = shost_priv(ioc->sh);
	VirtTarget *vtarget = NULL;
	struct mptsas_target_reset_event *target_reset_list;
	u8		id, channel;

	id = sas_event_data->TargetID;
	channel = sas_event_data->Bus;

	vtarget = mptsas_find_vtarget(ioc, channel, id);
	if (vtarget) {
		mptsas_block_io_starget(vtarget->starget);
		vtarget->deleted = 1;
	}

	target_reset_list = kzalloc(sizeof(struct mptsas_target_reset_event),
	    GFP_ATOMIC);
	if (!target_reset_list) {
		dfailprintk(ioc, printk(MYIOC_s_WARN_FMT
			"%s, failed to allocate mem @%d..!!\n",
			ioc->name, __func__, __LINE__));
		return;
	}

	memcpy(&target_reset_list->sas_event_data, sas_event_data,
		sizeof(*sas_event_data));
	list_add_tail(&target_reset_list->list, &hd->target_reset_list);

	target_reset_list->time_count = jiffies;

	if (mptsas_target_reset(ioc, channel, id)) {
		target_reset_list->target_reset_issued = 1;
	}
}
