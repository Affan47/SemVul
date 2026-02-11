pm6k_init(int fd, unsigned long *id, unsigned long *extra)
{
	int i = 0;
	unsigned char cmd[6] = {0xF1, 0x00, 0x00, 0x00, 0x00, 0x0E};
	unsigned char data[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


	if (write(fd, cmd, sizeof(cmd)) != sizeof(cmd))
		return -1;


	for(i=0;i<sizeof(data);i++)
		if (readchar(fd, &data[i], 100)<0)
			break ;

	return 0;
}
