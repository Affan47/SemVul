Devices_H_DiskInfo(void)
{
	static UBYTE info[16] = {
		0x20,
		0x00,
		0xff, 0xff,
		0xff, 0xff,
		'H', 'D', 'I', 'S', 'K', '1' , ' ', ' ',
		1,
		1
	};
	int devnum;

	if (devbug)
		Log_print("Get Disk Information Command");

	devnum = Devices_GetNumber(FALSE);
	if (devnum < 0)
		return;

	info[11] = (UBYTE) ('1' + devnum);
	info[15] = (UBYTE) (1 + devnum);
	MEMORY_CopyToMem(info, (UWORD) MEMORY_dGetWordAligned(Devices_ICBLLZ), 16);

	CPU_regY = 1;
	CPU_ClrN;
}
