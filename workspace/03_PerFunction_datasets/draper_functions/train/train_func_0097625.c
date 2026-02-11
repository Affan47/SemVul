swan_vk_send_line(struct swan_vk_command_option *opt, int x0, int y0, int x1, int y1)
{
	int ret;
	int fd;

	fd = swan_vk_link_server(opt);
	if (fd < 0)
	{
		return fd;
	}

	ret = swan_vk_send_line_base(fd, x0, y0, x1, y1);
	if (ret < 0)
	{
		pr_red_info("swan_vk_send_line");
	}

	close(fd);

	return ret;
}
