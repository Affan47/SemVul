net_multicast_join(int sockfd, const sockaddr_t *addr, size_t addrsize, const char *ifname, unsigned int ifindex)
{
	sockaddr_any_t *any = (sockaddr_any_t *)addr;

	switch (any->any.sa_family)
	{
		case AF_INET:
		{
			struct ip_mreq mreq[1];
			struct ifreq ifreq[1];

			memcpy(&mreq->imr_multiaddr, &any->in.sin_addr, sizeof mreq->imr_multiaddr);

			if (!ifindex && !ifname)
			{
				mreq->imr_interface.s_addr = htonl(INADDR_ANY);
			}
			else
			{
				if (ifname)
				{
					strlcpy(ifreq->ifr_name, ifname, IFNAMSIZ);
				}
				else if (ifindex)
				{
					if (!if_indextoname(ifindex, ifreq->ifr_name))
						return set_errno(ENXIO);
				}

				if (ioctl(sockfd, SIOCGIFADDR, ifreq) == -1)
					return -1;

				memcpy(&mreq->imr_interface, &((sockaddr_in_t *)&ifreq->ifr_addr)->sin_addr, sizeof mreq->imr_multiaddr);
			}

			return setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, mreq, sizeof mreq);
		}

#ifdef AF_INET6
		case AF_INET6:
		{
			struct ipv6_mreq mreq[1];

			memcpy(&mreq->ipv6mr_multiaddr, &any->in6.sin6_addr, sizeof mreq->ipv6mr_multiaddr);

			if (ifname)
			{
				if ((mreq->ipv6mr_interface = if_nametoindex(ifname)) == 0)
					return set_errno(ENXIO);
			}
			else
			{
				mreq->ipv6mr_interface = ifindex;
			}

			return setsockopt(sockfd, IPPROTO_IPV6, IPV6_JOIN_GROUP, mreq, sizeof mreq);
		}
#endif

		default:
			return set_errno(EPROTONOSUPPORT);
	}
}
