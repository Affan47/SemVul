send_response(int sockfd, char* content, int offset, int len)
{
	struct message msg;

	extern int wrapper(struct message*, char*, int, int);
	extern int _send(int sockfd, const struct message* msg);

	if (FUC_FAILURE == wrapper(&msg, content, offset, len))
	{
		return FUC_FAILURE;
	}

	if (FUC_FAILURE == _send(sockfd, &msg))
	{
		return FUC_FAILURE;
	}

	return FUC_SUCCESS;
}
