socketConnect(mail::loginInfo &loginInfo,
			       const char *plainservice,
			       const char *sslservice)
{

#if HAVE_LIBCOURIERTLS

#else
	if (loginInfo.use_ssl)
		return "SSL support not available.";

#endif

	struct addrinfo *res;

	string server=loginInfo.server, portnum;
	const char *port=loginInfo.use_ssl ? sslservice:plainservice;
	size_t n=server.find(':');

	if (n != std::string::npos)
	{
		port=NULL;
		portnum=server.substr(n+1);
		server=server.substr(0, n);
	}

	if (loginInfo.options.count("debugio") > 0)
		ioDebugFlag=true;

	struct addrinfo hints;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family=PF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;

	int errcode=getaddrinfo(server.c_str(),	port, &hints, &res);

	if (errcode)
		return gai_strerror(errcode);

	if (!port)
	{
		int nport=atoi(portnum.c_str());

		if (nport <= 0 || nport > 65535)
		{
			freeaddrinfo(res);
			return strerror(EINVAL);
		}

		switch (res->ai_addr->sa_family) {
		case AF_INET:
			((struct sockaddr_in *)res->ai_addr)
				->sin_port=htons(nport);
			break;
#ifdef AF_INET6
		case AF_INET6:
			((struct sockaddr_in6 *)res->ai_addr)
				->sin6_port=htons(nport);
			break;
#endif
		default:
			freeaddrinfo(res);
			return strerror(EAFNOSUPPORT);
		}
	}

	socketfd=socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	connecting=1;


	if (socketfd < 0 || fcntl(socketfd, F_SETFL, O_NONBLOCK) < 0 ||
	    fcntl(socketfd, F_SETFD, FD_CLOEXEC) < 0)
	{
		freeaddrinfo(res);
		return strerror(errno);
	}

#if HAVE_LIBCOURIERTLS

	if (loginInfo.use_ssl)
	{
		string errmsg= starttls(loginInfo, false);

		if (errmsg.size() > 0)
		{
			freeaddrinfo(res);
			return errmsg;
		}
	}
#endif

	if (sox_connect(socketfd, res->ai_addr, res->ai_addrlen) < 0)
	{
		freeaddrinfo(res);
		if (errno != EINPROGRESS)
			return strerror(errno);


	}
	else
	{
		freeaddrinfo(res);
		connecting=3;
	}

	return "";
}
