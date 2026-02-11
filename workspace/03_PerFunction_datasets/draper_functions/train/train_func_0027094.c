file_permition_tostring(mode_t mode, char *buff, char *buff_end)
{
	int i;
	u32 shift;
	const char *permition_table = "rwx";

	shift = 1 << 8;

	while (shift)
	{
		for (i = 0; i < 3 && buff < buff_end; i++, shift >>= 1, buff++)
		{
			if (mode & shift)
			{
				*buff = permition_table[i];
			}
			else
			{
				*buff = '-';
			}
		}
	}

	return buff;
}
