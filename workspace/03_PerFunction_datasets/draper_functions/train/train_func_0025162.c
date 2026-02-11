cavan_vfat_build_volume_label(const u8 name[11], char *buff, size_t size)
{
	const u8 *p;

	for (p = name + 11 - 1; p >= name; p--)
	{
		if (*p != 0x20)
		{
			size_t count;

			count = p - name + 1;
			if (count > size)
			{
				count = size;
			}

			buff = mem_copy(buff, name, count);
			break;
		}
	}

	*buff = 0;

	return buff;
}
