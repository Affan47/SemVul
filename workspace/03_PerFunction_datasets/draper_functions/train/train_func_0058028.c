do_ip_check_interface(DYN_DNS_CLIENT *p_self)
{
	struct ifreq ifr;
	in_addr_t new_ip;
	char *new_ip_str;
	int i;

	if (p_self == NULL)
	{
		return RC_INVALID_POINTER;
	}

	if (p_self->check_interface)
	{
		logit(LOG_INFO, MODULE_TAG "Checking for IP# change, querying interface %s",
		      p_self->check_interface);

		int sd = socket(PF_INET, SOCK_DGRAM, 0);

		if (sd < 0)
		{
			int code = os_get_socket_error();

			logit(LOG_WARNING, MODULE_TAG "Failed opening network socket: %s", strerror(code));
			return RC_IP_OS_SOCKET_INIT_FAILED;
		}

		memset(&ifr, 0, sizeof(struct ifreq));
		ifr.ifr_addr.sa_family = AF_INET;
		snprintf(ifr.ifr_name, IFNAMSIZ, "%s", p_self->check_interface);
		if (ioctl(sd, SIOCGIFADDR, &ifr) != -1)
		{
			new_ip = ntohl(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr);
			new_ip_str = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
		}
		else
		{
			int code = os_get_socket_error();

			logit(LOG_ERR, MODULE_TAG "Failed reading IP address of interface %s: %s",
			      p_self->check_interface, strerror(code));
			return RC_ERROR;
		}
		close(sd);
	}
	else
	{
		return RC_ERROR;
	}

	if (IN_ZERONET(new_ip) ||
	    IN_LOOPBACK(new_ip) ||
	    IN_LINKLOCAL(new_ip) ||
	    IN_MULTICAST(new_ip) ||
	    IN_EXPERIMENTAL(new_ip))
	{
		logit(LOG_WARNING, MODULE_TAG "Interface %s has invalid IP# %s",
		      p_self->check_interface, new_ip_str);
		return RC_ERROR;
	}

	int anychange = 0;

	for (i = 0; i < p_self->info_count; i++)
	{
		DYNDNS_INFO_TYPE *info = &p_self->info[i];

		info->my_ip_has_changed = strcmp(info->my_ip_address.name, new_ip_str) != 0;
		if (info->my_ip_has_changed)
		{
			anychange++;
			strcpy(info->my_ip_address.name, new_ip_str);
		}
	}

	if (!anychange)
	{
		logit(LOG_INFO, MODULE_TAG "No IP# change detected, still at %s", new_ip_str);
	}

	return RC_OK;
}
