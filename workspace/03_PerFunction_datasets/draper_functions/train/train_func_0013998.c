create_localport_session(int fd, LocalPort *lport,
					    const char *service, const char *port,
					    const char *localport, const char *password)
{

    int newsessionnum = next_session_number();

    localportSession *newsession = new localportSession(*this, lport, 0, newsessionnum,
						  (char *)localport, fd);
    if (newsession->new_session((unsigned char *)remnode, (char *)service, (char *)port, (char *)password, 0) == -1)
    {
	delete newsession;
	return -1;
    }
    sessions[newsessionnum] = newsession;
    return 0;
}
