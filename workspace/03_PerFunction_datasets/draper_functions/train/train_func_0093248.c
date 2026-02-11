setup_streams(void) {
	struct stream_list *dp, *up;
	int i;
	isc_boolean_t link_is_set;

	for (dp = downstreams; dp; dp = dp->next) {

		if (dp->ifp->v6address_count == 0)
			log_fatal("Interface '%s' has no IPv6 addresses.",
				  dp->ifp->name);


		if (IN6_IS_ADDR_UNSPECIFIED(&dp->link.sin6_addr))
			link_is_set = ISC_FALSE;
		else
			link_is_set = ISC_TRUE;
		for (i = 0; i < dp->ifp->v6address_count; i++) {
			if (IN6_IS_ADDR_LINKLOCAL(&dp->ifp->v6addresses[i]))
				continue;
			if (!link_is_set)
				break;
			if (!memcmp(&dp->ifp->v6addresses[i],
				    &dp->link.sin6_addr,
				    sizeof(dp->link.sin6_addr)))
				break;
		}
		if (i == dp->ifp->v6address_count)
			log_fatal("Can't find link address for interface '%s'.",
				  dp->ifp->name);
		if (!link_is_set)
			memcpy(&dp->link.sin6_addr,
			       &dp->ifp->v6addresses[i],
			       sizeof(dp->link.sin6_addr));


		if (dp->id == -1)
			dp->id = dp->ifp->index;
	}

	for (up = upstreams; up; up = up->next) {
		up->link.sin6_port = local_port;
		up->link.sin6_family = AF_INET6;
#ifdef HAVE_SA_LEN
		up->link.sin6_len = sizeof(up->link);
#endif

		if (up->ifp->v6address_count == 0)
			log_fatal("Interface '%s' has no IPv6 addresses.",
				  up->ifp->name);
	}
}
