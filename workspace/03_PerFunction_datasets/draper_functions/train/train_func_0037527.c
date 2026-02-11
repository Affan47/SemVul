file_table_for_each(void (*callback)(void *, gfarm_int32_t), void *closure)
{
	gfarm_int32_t net_fd;

	if (file_table == NULL)
		return;

	for (net_fd = 0; net_fd < file_table_size; net_fd++) {
		if (file_table[net_fd].local_fd != -1)
			(*callback)(closure, net_fd);
	}
}
