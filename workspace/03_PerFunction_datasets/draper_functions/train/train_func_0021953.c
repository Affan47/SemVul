receive_packet6(struct interface_info *interface,
		unsigned char *buf, size_t len,
		struct sockaddr_in6 *from, struct in6_addr *to_addr,
		unsigned int *if_idx)
{
	struct msghdr m;
	struct iovec v;
	int result;
	struct cmsghdr *cmsg;
	struct in6_pktinfo *pktinfo;


	if (control_buf == NULL) {
		allocate_cmsg_cbuf();
		if (control_buf == NULL) {
			log_error("receive_packet6: unable to allocate cmsg "
				  "header");
			return(ENOMEM);
		}
	}
	memset(control_buf, 0, control_buf_len);


	memset(&m, 0, sizeof(m));


	m.msg_name = from;
	m.msg_namelen = sizeof(*from);


	v.iov_base = buf;
	v.iov_len = len;
	m.msg_iov = &v;
	m.msg_iovlen = 1;


	m.msg_control = control_buf;
	m.msg_controllen = control_buf_len;

	result = recvmsg(interface->rfdesc, &m, 0);

	if (result >= 0) {


		cmsg = CMSG_FIRSTHDR(&m);
		while (cmsg != NULL) {
			if ((cmsg->cmsg_level == IPPROTO_IPV6) &&
			    (cmsg->cmsg_type == IPV6_PKTINFO)) {
				pktinfo = (struct in6_pktinfo *)CMSG_DATA(cmsg);
				*to_addr = pktinfo->ipi6_addr;
				*if_idx = pktinfo->ipi6_ifindex;

				return (result);
			}
			cmsg = CMSG_NXTHDR(&m, cmsg);
		}


		result = -1;
		errno = EIO;
	}

	return (result);
}
