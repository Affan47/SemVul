soakupdata(const struct api_fd * fdp)
{
	int	bcount;
	struct	api_msg	msg;
	char	buffer[XTA_BUFFSIZE];

	while  (gspool_rmsg(fdp, &msg) == 0  &&  msg.code == API_DATAOUT  &&
		(bcount = ntohs(msg.un.jobdata.nbytes)) > 0)
		if  (gspool_read(fdp->sockfd, buffer, (unsigned) bcount) != 0)
			return;
}
