GetSubNetForSocketAndIp(__UDPSOCKET__ inSock, RakNet::RakString inIpString)
{
	RakNet::RakString netMaskString;
	RakNet::RakString ipString;


#if   defined(WINDOWS_STORE_RT)
	RakAssert("Not yet supported" && 0);
	return "";
#elif defined(_WIN32)
	INTERFACE_INFO InterfaceList[20];
	unsigned long nBytesReturned;
	if (WSAIoctl(inSock, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList,
		sizeof(InterfaceList), &nBytesReturned, 0, 0) == SOCKET_ERROR) {
			return "";
	}

	int nNumInterfaces = nBytesReturned / sizeof(INTERFACE_INFO);

	for (int i = 0; i < nNumInterfaces; ++i)
	{
		sockaddr_in *pAddress;
		pAddress = (sockaddr_in *) & (InterfaceList[i].iiAddress);
		ipString=inet_ntoa(pAddress->sin_addr);

		if (inIpString==ipString)
		{
			pAddress = (sockaddr_in *) & (InterfaceList[i].iiNetmask);
			netMaskString=inet_ntoa(pAddress->sin_addr);
			return netMaskString;
		}
	}
	return "";
#else

	int fd,fd2;
	fd2 = socket__(AF_INET, SOCK_DGRAM, 0);

	if(fd2 < 0)
	{
		return "";
	}

	struct ifconf ifc;
	char          buf[1999];
	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if(ioctl(fd2, SIOCGIFCONF, &ifc) < 0)
	{
		return "";
	}

	struct ifreq *ifr;
	ifr         = ifc.ifc_req;
	int intNum = ifc.ifc_len / sizeof(struct ifreq);
	for(int i = 0; i < intNum; i++)
	{
		ipString=inet_ntoa(((struct sockaddr_in *)&ifr[i].ifr_addr)->sin_addr);

		if (inIpString==ipString)
		{
			struct ifreq ifr2;
			fd = socket__(AF_INET, SOCK_DGRAM, 0);
			if(fd < 0)
			{
				return "";
			}
			ifr2.ifr_addr.sa_family = AF_INET;

			strncpy(ifr2.ifr_name, ifr[i].ifr_name, IFNAMSIZ-1);

			ioctl(fd, SIOCGIFNETMASK, &ifr2);

			close(fd);
			close(fd2);
			netMaskString=inet_ntoa(((struct sockaddr_in *)&ifr2.ifr_addr)->sin_addr);

			return netMaskString;
		}
	}

	close(fd2);
	return "";

#endif

}
