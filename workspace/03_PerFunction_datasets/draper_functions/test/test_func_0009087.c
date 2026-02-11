ctrlRequest(const char *cmd, char *buf, size_t *buflen)
{
	int ret;

	if (ctrl_conn == NULL)
		return -3;
	ret = wpa_ctrl_request(ctrl_conn, cmd, strlen(cmd), buf, buflen, NULL);
	if (ret == -2)
		printf("'%s' command timed out.\n", cmd);
	else if (ret < 0)
		printf("'%s' command failed.\n", cmd);

	return ret;
}
