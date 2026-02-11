SendMotd(int sockfd)

{
	char line[MAXLINE + 1];
	char *final;
	char *ch;
	FILE *fp;

	if ((fp = fopen(DccMotdFile, "r")) == NULL)
	{
		writesocket(sockfd, "MOTD file missing\r\n");
		return;
	}

	while (fgets(line, sizeof(line), fp))
	{
		if ((ch = strchr(buffer, '\n')) != NULL)
			*ch = '\0';

		if (*line != '\0')
		{
			final = Substitute(NULL, line, sockfd);
			if (final && (final != (char *) -1))
			{
				writesocket(sockfd, final);
				MyFree(final);
			}
		}

		writesocket(sockfd, "\r\n");
	}

	fclose(fp);
}
