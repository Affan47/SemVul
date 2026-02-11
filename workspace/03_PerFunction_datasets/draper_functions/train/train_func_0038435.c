CheckCancel(char *msgid, bool JustReturn)
{
    char		localfrom[SMBUF];
    char	*p;
    char		buff[BUFSIZ];
    char		remotefrom[SMBUF];


    fprintf(ToServer, "head %s\r\n", msgid);
    SafeFlush(ToServer);
    if (fgets(buff, sizeof buff, FromServer) == NULL
     || atoi(buff) != NNTP_OK_HEAD) {
	if (JustReturn)
	    return;
        die("server has no such article");
    }


    remotefrom[0] = '\0';
    while (fgets(buff, sizeof buff, FromServer) != NULL) {
	if ((p = strchr(buff, '\r')) != NULL)
	    *p = '\0';
	if ((p = strchr(buff, '\n')) != NULL)
	    *p = '\0';
	if (buff[0] == '.' && buff[1] == '\0')
	    break;
        if (strncasecmp(buff, "Sender:", 7) == 0)
            strlcpy(remotefrom, TrimSpaces(&buff[7]), SMBUF);
        else if (remotefrom[0] == '\0' && strncasecmp(buff, "From:", 5) == 0)
            strlcpy(remotefrom, TrimSpaces(&buff[5]), SMBUF);
    }
    if (remotefrom[0] == '\0') {
	if (JustReturn)
	    return;
        die("article is garbled");
    }
    HeaderCleanFrom(remotefrom);


    strlcpy(localfrom, HDR(_sender) ? HDR(_sender) : HDR(_from), SMBUF);
    HeaderCleanFrom(localfrom);


    if (strcasecmp(localfrom, remotefrom) != 0)
        die("article was posted by \"%s\" and you are \"%s\"", remotefrom,
            localfrom);
}
