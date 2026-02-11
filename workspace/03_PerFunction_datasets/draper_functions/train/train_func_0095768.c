o_motd_display(struct Luser *lptr, int ac, char **av, int
                           sockfd)
{
	o_RecordCommand(sockfd, "MOTD DISPLAY");

	if (!Network->LogonNewsFile.Contents)
	{
		os_notice(lptr, sockfd,
		          "There is nothing in MOTD");
		return;
	}

	SendMessageFile(lptr, &Network->LogonNewsFile);
}
