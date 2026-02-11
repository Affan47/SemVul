arp_set(char **args)
{
	char *host;
	struct arpreq req;
	struct sockaddr sa;
	int flags;

	memset(&req, 0, sizeof(req));

	host = *args++;
	if (ap->input(host, &sa) < 0) {
		bb_herror_msg_and_die("%s", host);
	}

	memcpy(&req.arp_pa, &sa, sizeof(struct sockaddr));


	if (*args == NULL) {
		bb_error_msg_and_die("need hardware address");
	}
	if (option_mask32 & ARP_OPT_D) {
		arp_getdevhw(*args++, &req.arp_ha, hw_set ? hw : NULL);
	} else {
		if (hw->input(*args++, &req.arp_ha) < 0) {
			bb_error_msg_and_die("invalid hardware address");
		}
	}


	flags = ATF_PERM | ATF_COM;
	while (*args != NULL) {
		switch (index_in_strings(options, *args)) {
		case 0:
			flags |= ATF_PUBL;
			args++;
			break;
		case 1:
			flags &= ~ATF_PUBL;
			args++;
			break;
		case 2:
			flags &= ~ATF_PERM;
			args++;
			break;
		case 3:
			flags |= ATF_USETRAILERS;
			args++;
			break;
		case 4:
#ifdef HAVE_ATF_DONTPUB
			flags |= ATF_DONTPUB;
#else
			bb_error_msg("feature ATF_DONTPUB is not supported");
#endif
			args++;
			break;
		case 5:
#ifdef HAVE_ATF_MAGIC
			flags |= ATF_MAGIC;
#else
			bb_error_msg("feature ATF_MAGIC is not supported");
#endif
			args++;
			break;
		case 6:
			if (*++args == NULL)
				bb_show_usage();
			device = *args;
			args++;
			break;
		case 7:
			if (*++args == NULL)
				bb_show_usage();
			if (strcmp(*args, "255.255.255.255") != 0) {
				host = *args;
				if (ap->input(host, &sa) < 0) {
					bb_herror_msg_and_die("%s", host);
				}
				memcpy(&req.arp_netmask, &sa, sizeof(struct sockaddr));
				flags |= ATF_NETMASK;
			}
			args++;
			break;
		default:
			bb_show_usage();
			break;
		}
	}


	req.arp_flags = flags;

	strncpy(req.arp_dev, device, sizeof(req.arp_dev));


	if (option_mask32 & ARP_OPT_v)
		bb_error_msg("SIOCSARP()");
	xioctl(sockfd, SIOCSARP, &req);
	return 0;
}
