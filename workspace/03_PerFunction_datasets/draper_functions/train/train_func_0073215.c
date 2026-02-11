send_reply(int cfd, struct message *msg)
{
	int res = send(cfd, msg, sizeof(struct message), MSG_NOSIGNAL);
	if (res == -1)
		perror("ulockmgr_server: sending reply");
#ifdef DEBUG
	fprintf(stderr, "ulockmgr_server: error: %i\n", msg->error);
#endif
}
