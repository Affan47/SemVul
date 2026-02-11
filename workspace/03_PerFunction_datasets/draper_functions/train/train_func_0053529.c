siocgifconf(struct ifconf *ifcp)
{
	caddr_t	buf, new_buf;
	int	s, len;


	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == -1) {
		log_error("siocgifconf: "
		    "socket (AF_INET, SOCK_DGRAM, 0) failed");
		return -1;
	}
	len = sizeof(struct ifreq) * INITIAL_IFREQ_COUNT;
	buf = 0;
	while (1) {


		new_buf = realloc(buf, len);
		if (!new_buf) {
			log_error("siocgifconf: realloc (%p, %d) failed", buf,
			    len);
			goto err;
		}
		ifcp->ifc_len = len;
		ifcp->ifc_buf = buf = new_buf;
		if (ioctl(s, SIOCGIFCONF, ifcp) == -1) {
			log_error("siocgifconf: ioctl (%d, SIOCGIFCONF, ...) "
			    "failed", s);
			goto err;
		}


		if (len - ifcp->ifc_len >= sizeof(struct ifreq))
			break;
		len *= 2;
	}
	close(s);
	return 0;

err:
	if (buf)
		free(buf);
	ifcp->ifc_len = 0;
	ifcp->ifc_buf = 0;
	close(s);
	return -1;
}
