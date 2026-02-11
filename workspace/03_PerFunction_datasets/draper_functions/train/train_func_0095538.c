dump_maj_right(const uint8_t* bits, int row, int major)
{
	int minor;

	for (minor = 0; minor < get_major_minors(XC6SLX9, major); minor++)
		printf_clock(&bits[minor*FRAME_SIZE], row, major, minor);
	for (minor = 0; minor < get_major_minors(XC6SLX9, major); minor++)
		printf_frames(&bits[minor*FRAME_SIZE],  1,
			row, major, minor,  0,  1);
	return 0;
}
