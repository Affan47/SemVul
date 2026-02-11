GetConfigLine(int *fd, char **tline)
{
	FvwmPacket *packet;
	int body_count;

	if (first_pass)
	{
		SendText(fd, "Send_ConfigInfo", 0);
		first_pass = 0;
	}

	do
	{
		packet = ReadFvwmPacket(fd[1]);
		if (packet == NULL || packet->type == M_END_CONFIG_INFO)
		{
			*tline = NULL;
			return;
		}
	} while (packet->type != M_CONFIG_INFO);


	*tline = (char *)&(packet->body[3]);
	body_count = FvwmPacketBodySize(*packet) * sizeof(unsigned long);

	while (body_count > 0 && isspace((unsigned char)**tline))
	{
		(*tline)++;
		--body_count;
	}
}
