cavan_cache_fill(struct cavan_cache *cache, char *buff, size_t size, size_t reserved, u32 timeout)
{
	char *buff_bak = buff;
	char *buff_end = buff + size;

	while (buff < buff_end)
	{
		ssize_t rdlen = cavan_cache_read(cache, buff, buff_end - buff, reserved, timeout);
		if (rdlen < 0)
		{
			pr_red_info("cavan_cache_read");
			return rdlen;
		}

		if (rdlen == 0)
		{
			size = buff - buff_bak;
			break;
		}

		buff += rdlen;
	}

	return size;
}
