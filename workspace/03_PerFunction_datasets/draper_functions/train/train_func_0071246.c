drive_motor (drive * drv, bool off)
{
	if (drv->motoroff && !off) {
		drv->dskready_up_time = DSKREADY_UP_TIME;
		rand_shifter (drv);
#ifdef DRIVESOUND
		driveclick_motor (drv - floppy, drv->dskready_down_time == 0 ? 2 : 1);
#endif
		if (disk_debug_logging > 1)
			write_log (_T(" ->motor on"));
	}
	if (!drv->motoroff && off) {
		drv->drive_id_scnt = 0;
		drv->dskready_down_time = DSKREADY_DOWN_TIME;
#ifdef DRIVESOUND
		driveclick_motor (drv - floppy, 0);
#endif
#ifdef DEBUG_DRIVE_ID
		write_log (_T("drive_motor: Selected DF%d: reset id shift reg.\n"),drv-floppy);
#endif
		if (disk_debug_logging > 1)
			write_log (_T(" ->motor off"));
		if (currprefs.cpu_model <= 68010 && currprefs.m68k_speed == 0) {
			drv->motordelay = 1;
			event2_newevent2 (30, drv - floppy, motordelay_func);
		}
	}
	drv->motoroff = off;
	if (drv->motoroff) {
		drv->dskready = 0;
		drv->dskready_up_time = 0;
	} else {
		drv->dskready_down_time = 0;
	}
#ifdef CATWEASEL
	if (drv->catweasel)
		catweasel_set_motor (drv->catweasel, !drv->motoroff);
#endif
}
