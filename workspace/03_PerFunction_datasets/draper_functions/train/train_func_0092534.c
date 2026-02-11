DoUlog(void *p)
{


	static struct sockaddr_nl	tSenderAddress = {.nl_family = AF_NETLINK,
																				.nl_pid = 0,
																				.nl_groups = FBLED_ULOG_GROUP_MASK,
																				.nl_pad = 0};
	ssize_t									tSizeRead;
	socklen_t								tSenderAddressLength = sizeof(tSenderAddress);
	struct nlmsghdr 					*ptNetlinkHeader;
	ulog_packet_msg_t				*ptUlogHeader;
	tUlogPriv							*ptUlogPrivData;

	ptUlogPrivData = (tUlogPriv *)p;

	if (-1 == ptUlogPrivData->iUlogSocket)
		return;


	if (-1 == (tSizeRead = recvfrom(ptUlogPrivData->iUlogSocket, ptUlogPrivData->pUlogDatagram, ULOG_RCVBUF,
	                                  0, (struct sockaddr *)&tSenderAddress,  &tSenderAddressLength)))
		return;

	if (sizeof(tSenderAddress) != tSenderAddressLength)
		return;
	if (   tSenderAddress.nl_pid != 0
		|| tSenderAddress.nl_family != AF_NETLINK
		|| 0 == ((1 << (tSenderAddress.nl_groups-1)) & FBLED_ULOG_GROUP_MASK))
		return;

	for ( ptNetlinkHeader = (struct nlmsghdr *)ptUlogPrivData->pUlogDatagram;

	     	NLMSG_OK(ptNetlinkHeader,tSizeRead) &&


	     	ULOG_TYPE == ptNetlinkHeader->nlmsg_type;

	     	ptNetlinkHeader = NLMSG_NEXT(ptNetlinkHeader,tSizeRead))
		{


			ptUlogHeader = (ulog_packet_msg_t *)NLMSG_DATA(ptNetlinkHeader);

			if (ULMSG_OK(ptUlogHeader,ptNetlinkHeader->nlmsg_len - NLMSG_HDRLEN))
			{
				if (0 == memcmp(ptUlogHeader->indev_name,"eth0",4) || 0 == memcmp(ptUlogHeader->outdev_name,"eth0",4))
					ptUlogPrivData->auDevBlipCount[0] = ULOG_BLIPS;
				if (0 == memcmp(ptUlogHeader->indev_name,"eth1",4) || 0 == memcmp(ptUlogHeader->outdev_name,"eth1",4))
					ptUlogPrivData->auDevBlipCount[1] = ULOG_BLIPS;
				if (0 == memcmp(ptUlogHeader->indev_name,"eth2",4) || 0 == memcmp(ptUlogHeader->outdev_name,"eth2",4))
					ptUlogPrivData->auDevBlipCount[2] = ULOG_BLIPS;
			}
		}
}
