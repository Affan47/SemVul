setcookieuin(std::string cookie, std::string uin)
{
	char buffer[BUFFER_SIZE];
	class Socket cookiesock(AF_UNIX, SOCK_STREAM);

	if (!cookiesock.connectsocket(COOKIE_SOCKET,""))
	{
		syslog(LOG_ERR, PROTOCOL_NAME ": Couldn't connect to cookie socket");
		return false;
	}

	memset(buffer, 0, BUFFER_SIZE);
	snprintf(buffer, BUFFER_SIZE - 1, "set\n%s\n%s\n", cookie.c_str(), uin.c_str());

	if (!cookiesock.sendalldata(buffer, strlen(buffer)))
	{
		syslog(LOG_ERR, PROTOCOL_NAME ": Couldn't send cookie set request");
		cookiesock.closesocket();
		return false;
	}

	cookiesock.closesocket();

	return true;
}
