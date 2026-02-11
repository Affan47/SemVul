partition_read_label_base(const char *dev_path, const char *read_cmd, char *buff, size_t buff_len)
{
	ssize_t readlen;

	readlen = buff_command2(buff, buff_len, "%s %s", read_cmd, dev_path);
	if (readlen < 0)
	{
		return readlen;
	}

	buff[readlen] = 0;
	text_tok(buff, " \n");

	return readlen;
}
