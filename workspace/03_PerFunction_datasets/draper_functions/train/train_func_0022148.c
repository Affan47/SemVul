extract_ipv6_addr(struct ifaddrmsg *msg, int bytes,
						struct in6_addr *addr,
						struct in6_addr *local)
{
	struct rtattr *attr;

	for (attr = IFA_RTA(msg); RTA_OK(attr, bytes);
					attr = RTA_NEXT(attr, bytes)) {
		switch (attr->rta_type) {
		case IFA_ADDRESS:
			if (addr != NULL)
				*addr = *((struct in6_addr *) RTA_DATA(attr));
			break;
		case IFA_LOCAL:
			if (local != NULL)
				*local = *((struct in6_addr *) RTA_DATA(attr));
			break;
		}
	}
}
