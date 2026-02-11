read_str(FILE *fp, char buf[], int buf_size, char exaust)
{
	if (buf_size <= 0)
		return -1;

	int i = 0;
	for (; i < buf_size - 1 && fread(buf + i, 1, 1, fp) && buf[i]; i++);
	buf[i] = 0;

	if (i == buf_size - 1 && exaust)
	{
		char c = 0;
		while (fread(&c, 1, 1, fp) && c);

	}

	return i;
}
