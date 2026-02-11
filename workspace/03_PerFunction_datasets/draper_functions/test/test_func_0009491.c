reset_drive_gui (int num)
{
	gui_data.drive_disabled[num] = 0;
	gui_data.df[num][0] = 0;
	gui_data.crc32[num] = 0;
	if (currprefs.floppyslots[num].dfxtype < 0)
		gui_data.drive_disabled[num] = 1;
}
