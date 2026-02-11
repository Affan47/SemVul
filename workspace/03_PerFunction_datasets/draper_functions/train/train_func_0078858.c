SIO_WriteStatusBlock(int unit, const UBYTE *buffer)
{
	int size;
#ifdef DEBUG
	Log_print("Write Status-Block: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
		buffer[0], buffer[1], buffer[2], buffer[3],
		buffer[4], buffer[5], buffer[6], buffer[7],
		buffer[8], buffer[9], buffer[10], buffer[11]);
#endif
	if (SIO_drive_status[unit] == SIO_OFF)
		return 0;


	size = buffer[6] * 256 + buffer[7];
	if (size == 128 || size == 256)
		SIO_format_sectorsize[unit] = size;

	SIO_format_sectorcount[unit] = buffer[0] * (buffer[2] * 256 + buffer[3]) * (buffer[4] + 1);
	if (SIO_format_sectorcount[unit] < 1 || SIO_format_sectorcount[unit] > 65535)
		SIO_format_sectorcount[unit] = 720;
	return 'C';
}
