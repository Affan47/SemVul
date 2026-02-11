csio_hostname(uint8_t *buf, size_t buf_len)
{
	if (snprintf(buf, buf_len, "%s", init_utsname()->nodename) > 0)
		return 0;
	return -1;
}
