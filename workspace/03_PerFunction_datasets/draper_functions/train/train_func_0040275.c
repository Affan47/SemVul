generic_ide_suspend(struct device *dev, pm_message_t mesg)
{
	ide_drive_t *drive = to_ide_device(dev);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	ide_hwif_t *hwif = drive->hwif;
	struct request *rq;
	struct ide_pm_state rqpm;
	int ret;

	if (ide_port_acpi(hwif)) {

		if ((drive->dn & 1) == 0 || pair == NULL)
			ide_acpi_get_timing(hwif);
	}

	memset(&rqpm, 0, sizeof(rqpm));
	rq = blk_get_request(drive->queue, READ, __GFP_RECLAIM);
	rq->cmd_type = REQ_TYPE_ATA_PM_SUSPEND;
	rq->special = &rqpm;
	rqpm.pm_step = IDE_PM_START_SUSPEND;
	if (mesg.event == PM_EVENT_PRETHAW)
		mesg.event = PM_EVENT_FREEZE;
	rqpm.pm_state = mesg.event;

	ret = blk_execute_rq(drive->queue, NULL, rq, 0);
	blk_put_request(rq);

	if (ret == 0 && ide_port_acpi(hwif)) {

		if ((drive->dn & 1) || pair == NULL)
			ide_acpi_set_state(hwif, 0);
	}

	return ret;
}
