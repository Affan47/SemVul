cm_netlink_fd_h(struct tevent_context *ec,
		struct tevent_fd *fde, uint16_t flags, void *pvt)
{
	struct cm_context *ctx = pvt;
	char buf[0x10000];
	int len;
	struct timeval later;
	struct sockaddr_storage nlsrc;
	socklen_t nlsrclen;


	if ((ctx == NULL) || (ctx->netlink < 0)) {
		return;
	}


	cm_log(3, "Got netlink traffic.\n");
	memset(&nlsrc, 0, sizeof(nlsrc));
	nlsrclen = sizeof(nlsrc);
	while ((len = recvfrom(ctx->netlink, buf, sizeof(buf), 0,
			       (struct sockaddr *) &nlsrc, &nlsrclen)) != -1) {
		switch (len) {
		case 0:
			cm_log(3, "Got EOF from netlink socket.\n");
			talloc_free(fde);
			close(ctx->netlink);
			ctx->netlink = -1;
			break;
		default:
			cm_log(3, "Got %d bytes from netlink socket.\n", len);
			break;
		}
		memset(&nlsrc, 0, sizeof(nlsrc));
		nlsrclen = 0;
		if (ctx->netlink == -1) {
			break;
		}
	}

	if (cm_netlink_pkt_is_route_change(buf, len,
					   (struct sockaddr *) &nlsrc,
					   nlsrclen) == 0) {
		talloc_free(ctx->netlink_delayed_event);
		later = tevent_timeval_current_ofs(CM_DELAY_NETLINK, 0);
		ctx->netlink_delayed_event = tevent_add_timer(talloc_parent(ctx), ctx,
							      later,
							      cm_netlink_delayed_h,
							      ctx);
	}

	if (len != 0) {
		cm_log(3, "No more netlink traffic (for now).\n");
	}
}
