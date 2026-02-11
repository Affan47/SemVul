ipvs_update_dest(ipvs_service_t *svc, ipvs_dest_t *dest)
{
	ipvs_servicedest_t svcdest;

	ipvs_func = ipvs_update_dest;
#ifdef LIBIPVS_USE_NL
	if (try_nl) {
		struct nl_msg *msg = ipvs_nl_message(IPVS_CMD_SET_DEST, 0);
		if (!msg) return -1;
		if (ipvs_nl_fill_service_attr(msg, svc))
			goto nla_put_failure;
		if (ipvs_nl_fill_dest_attr(msg, dest))
			goto nla_put_failure;
		return ipvs_nl_send_message(msg, ipvs_nl_noop_cb, NULL);

nla_put_failure:
		nlmsg_free(msg);
		return -1;
	}
#endif
	CHECK_COMPAT_SVC(svc, -1);
	CHECK_COMPAT_DEST(dest, -1);
	memcpy(&svcdest.svc, svc, sizeof(svcdest.svc));
	memcpy(&svcdest.dest, dest, sizeof(svcdest.dest));
	return setsockopt(sockfd, IPPROTO_IP, IP_VS_SO_SET_EDITDEST,
			  (char *)&svcdest, sizeof(svcdest));
out_err:
	return -1;
}
