adb_send_text(int sockfd, const char *text)
{
	int ret;
	ssize_t sendlen;
	size_t length;
	char buff[16];
	char status[256];

	length = text_len(text);

#if __WORDSIZE == 64
	sprintf(buff, "%04lx", length);
#else
	sprintf(buff, "%04x", length);
#endif

	sendlen = inet_send(sockfd, buff, 4);
	if (sendlen < 0)
	{
		pr_red_info("inet_send");
		return sendlen;
	}

	sendlen = inet_send(sockfd, text, length);
	if (sendlen < 0)
	{
		return sendlen;
	}

	ret = adb_read_status(sockfd, status, sizeof(status));
	if (ret < 0)
	{
		pr_red_info("status = %s", status);
		return ret;
	}

	return 0;
}
