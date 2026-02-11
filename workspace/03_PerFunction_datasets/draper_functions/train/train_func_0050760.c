o_motd_delete(struct Luser *lptr, int ac, char **av, int
                          sockfd)
{
	FILE *fp;

	o_RecordCommand(sockfd, "MOTD DELETE");

	if (!(fp = fopen(Network->LogonNewsFile.filename, "w")))
	{
		os_notice(lptr, sockfd,
		          "Cannot open MOTD file %s!",
		          Network->LogonNewsFile.filename);
		return;
	}

	fclose(fp);

	ReadMessageFile(&Network->LogonNewsFile);

	os_notice(lptr, sockfd, "MOTD deleted");
}
