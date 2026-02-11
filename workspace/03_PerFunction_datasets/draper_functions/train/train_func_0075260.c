mame_fwrite_swap(mame_file *file, const void *buffer, UINT32 length)
{
	UINT8 *buf;
	UINT8 temp;
	int res, i;


	buf = (UINT8 *)buffer;
	for (i = 0; i < length; i += 2)
	{
		temp = buf[i];
		buf[i] = buf[i + 1];
		buf[i + 1] = temp;
	}


	res = mame_fwrite(file, buffer, length);


	for (i = 0; i < length; i += 2)
	{
		temp = buf[i];
		buf[i] = buf[i + 1];
		buf[i + 1] = temp;
	}

	return res;
}
