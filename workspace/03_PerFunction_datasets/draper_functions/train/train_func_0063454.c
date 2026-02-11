blkdev_default_prefs (struct uae_prefs *p)
{
	for (int i = 0; i < MAX_TOTAL_SCSI_DEVICES; i++) {
		p->cdslots[i].name[0] = 0;
		p->cdslots[i].inuse = false;
		p->cdslots[i].type = SCSI_UNIT_DEFAULT;
		cdscsidevicetype[i] = SCSI_UNIT_DEFAULT;
	}
}
