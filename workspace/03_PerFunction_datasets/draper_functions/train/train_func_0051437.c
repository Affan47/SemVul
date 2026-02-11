getcookieuin(std::string cookie)
{
	char buffer[BUFFER_SIZE];
	class Socket cookiesock(AF_UNIX, SOCK_STREAM);

	memset(buffer, 0, BUFFER_SIZE);

	if (!cookiesock.connectsocket(COOKIE_SOCKET,""))
	{
		syslog(LOG_ERR, PROTOCOL_NAME ": Couldn't connect to cookie socket");
		return "";
	}

	memset(buffer, 0, BUFFER_SIZE);
	snprintf(buffer, BUFFER_SIZE - 1, "get\n%s\n", cookie.c_str());

	if (!cookiesock.sendalldata(buffer, strlen(buffer)))
	{
		syslog(LOG_ERR, PROTOCOL_NAME ": Couldn't send cookie get request");
		cookiesock.closesocket();
		return "";
	}

	memset(buffer, 0, BUFFER_SIZE);
	if (!cookiesock.recvline(buffer, BUFFER_SIZE))
	{
		syslog(LOG_ERR, PROTOCOL_NAME ": Didn't get a response from cookiemonster");
		cookiesock.closesocket();
		return "";
	}

	stripnewline(buffer);

	std::string uin;
	if (strlen(buffer)) uin = buffer;

	cookiesock.closesocket();

	return uin;
}
