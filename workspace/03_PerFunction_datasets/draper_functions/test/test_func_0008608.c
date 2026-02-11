network_client_recv_file(struct network_client *client, int fd, size_t size)
{
	ssize_t rdlen;
	char buff[2048];

	if (size == 0)
	{
		while (1)
		{
			rdlen = client->recv(client, buff, sizeof(buff));
			if (rdlen <= 0)
			{
				if (rdlen < 0)
				{
					return rdlen;
				}

				return size;
			}

			if (ffile_write(fd, buff, rdlen) < rdlen)
			{
				return -EIO;
			}

			size += rdlen;
		}
	}
	else
	{
		size_t size_bak = size;
		struct progress_bar bar;

		progress_bar_init(&bar, size);

		while (size)
		{

			rdlen = client->recv(client, buff, sizeof(buff));
			if (rdlen <= 0 || ffile_write(fd, buff, rdlen) < rdlen)
			{
				return -EIO;
			}

			size -= rdlen;
			progress_bar_add(&bar, rdlen);
		}

		progress_bar_finish(&bar);

		return size_bak;
	}
}
