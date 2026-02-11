update_drive_gui (int num)
{
	drive *drv = floppy + num;
	bool writ = dskdmaen == DSKDMA_WRITE && drv->state && !((selected | disabled) & (1 << num));

	if (drv->state == gui_data.drive_motor[num]
		&& drv->cyl == gui_data.drive_track[num]
		&& side == gui_data.drive_side
		&& drv->crc32 == gui_data.crc32[num]
		&& writ == gui_data.drive_writing[num]
		&& !_tcscmp (gui_data.df[num], currprefs.floppyslots[num].df))
		return;
	_tcscpy (gui_data.df[num], currprefs.floppyslots[num].df);
	gui_data.crc32[num] = drv->crc32;
	gui_data.drive_motor[num] = drv->state;
	gui_data.drive_track[num] = drv->cyl;
	gui_data.drive_side = side;
	gui_data.drive_writing[num] = writ;
	gui_led (num + LED_DF0, (gui_data.drive_motor[num] ? 1 : 0) | (gui_data.drive_writing[num] ? 2 : 0));
}
