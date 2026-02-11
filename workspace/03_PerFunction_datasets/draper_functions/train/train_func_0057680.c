mx_query(int fd, int b1, int *res)
{
	int buf[6] = { first_byte, 0x81, b1, 0, 0, 0 };
	int i;

	send_report(fd, 0x10, buf, 6);
	res[0] = -1;
	query_report(fd, 0x10, res, 6);

	if ((
		res[0]  != 0x01 ||
		res[1]  != 0x81 ||
		(res[2] != 0xb1 && res[2] != 0x08)
	) && (
		(res[0] != 0x02 && res[0] != 0x01) ||
		res[1]  != 0x81                    ||
		(res[2] != 0x0d && res[2] != 0x08)
	))
	{
		printf("bad answer:");
		for (i = 0; i < 6; ++i)
		{
		  printf("%02X ", res[i]);
		}
		printf("\n");
		return 0;
	}
	return 1;
}
