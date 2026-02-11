midway_serial_pic2_r(void)
{
	UINT8 result = 0;


	logerror("%06X:PIC data read (index=%d total=%d latch=%03X) =", activecpu_get_pc(), pic.index, pic.total, pic.latch);


	if (pic.latch & 0xf00)
		result = pic.latch & 0xff;


	else if (pic.index < pic.total)
		result = 0xff;

	logerror("%02X\n", result);
	return result;
}
