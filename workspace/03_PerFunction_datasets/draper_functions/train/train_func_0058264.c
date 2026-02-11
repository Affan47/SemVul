dump (FILE* fd)
{
	unsigned int size = max - min;
	fxStackBuffer buf;

	buf.fput("RANGE: %u - %u (%d bits)", min, max, size);
	PRINT_OR_SYSLOG(fd, buf);

	buf.reset();
	buf.fput("MAP: ");
	for (u_int i = 0; i < ((size+9)/10); i++)
		buf.fput("/  %3d   \\", (i+1)*10);
	PRINT_OR_SYSLOG(fd, buf);

	buf.reset();
	buf.fput("MAP: ");
	for (u_int i = 0; i < size; i++)
	{
		int b = i/8;
		int c = i%8;
		buf.fput("%c", (map[b] & (1<<c)) ? '1' : '0');
	}
	PRINT_OR_SYSLOG(fd, buf);

	buf.reset();
	buf.fput("MAP: ");
	for (u_int i = 0; i < ((size+7)/8); i++)
	{
		buf.fput("\\  %2.2X  /", i);
	}
	PRINT_OR_SYSLOG(fd, buf);
}
