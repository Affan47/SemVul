DISK_hsync (void)
{
	int dr;

	for (dr = 0; dr < MAX_FLOPPY_DRIVES; dr++) {
		drive *drv = &floppy[dr];
		if (drv->steplimit)
			drv->steplimit--;
	}
	if (indexdecay)
		indexdecay--;
	if (linecounter) {
		linecounter--;
		if (! linecounter)
			disk_dmafinished ();
		return;
	}
	DISK_update (maxhpos);
}
