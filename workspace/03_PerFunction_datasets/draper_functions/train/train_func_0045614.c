mptsas_volume_delete(MPT_ADAPTER *ioc, u8 id)
{
	struct scsi_device *sdev;
	int i;

	sdev = scsi_device_lookup(ioc->sh, MPTSAS_RAID_CHANNEL, id, 0);
	if (!sdev)
		return;
	if (!ioc->raid_data.pIocPg2)
		goto out;
	if (!ioc->raid_data.pIocPg2->NumActiveVolumes)
		goto out;
	for (i = 0; i < ioc->raid_data.pIocPg2->NumActiveVolumes; i++)
		if (ioc->raid_data.pIocPg2->RaidVolume[i].VolumeID == id)
			goto release_sdev;
 out:
	printk(MYIOC_s_INFO_FMT "removing raid volume, channel %d, "
	    "id %d\n", ioc->name, MPTSAS_RAID_CHANNEL, id);
	scsi_remove_device(sdev);
 release_sdev:
	scsi_device_put(sdev);
}
