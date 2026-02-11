dump_ep(int id, void *p, void *data)
{
	struct c4iw_ep *ep = p;
	struct c4iw_debugfs_data *epd = data;
	int space;
	int cc;

	space = epd->bufsize - epd->pos - 1;
	if (space == 0)
		return 1;

	if (ep->com.local_addr.ss_family == AF_INET) {
		struct sockaddr_in *lsin = (struct sockaddr_in *)
			&ep->com.local_addr;
		struct sockaddr_in *rsin = (struct sockaddr_in *)
			&ep->com.remote_addr;
		struct sockaddr_in *mapped_lsin = (struct sockaddr_in *)
			&ep->com.mapped_local_addr;
		struct sockaddr_in *mapped_rsin = (struct sockaddr_in *)
			&ep->com.mapped_remote_addr;

		cc = snprintf(epd->buf + epd->pos, space,
			      "ep %p cm_id %p qp %p state %d flags 0x%lx "
			      "history 0x%lx hwtid %d atid %d "
			      "conn_na %u abort_na %u "
			      "%pI4:%d/%d <-> %pI4:%d/%d\n",
			      ep, ep->com.cm_id, ep->com.qp,
			      (int)ep->com.state, ep->com.flags,
			      ep->com.history, ep->hwtid, ep->atid,
			      ep->stats.connect_neg_adv,
			      ep->stats.abort_neg_adv,
			      &lsin->sin_addr, ntohs(lsin->sin_port),
			      ntohs(mapped_lsin->sin_port),
			      &rsin->sin_addr, ntohs(rsin->sin_port),
			      ntohs(mapped_rsin->sin_port));
	} else {
		struct sockaddr_in6 *lsin6 = (struct sockaddr_in6 *)
			&ep->com.local_addr;
		struct sockaddr_in6 *rsin6 = (struct sockaddr_in6 *)
			&ep->com.remote_addr;
		struct sockaddr_in6 *mapped_lsin6 = (struct sockaddr_in6 *)
			&ep->com.mapped_local_addr;
		struct sockaddr_in6 *mapped_rsin6 = (struct sockaddr_in6 *)
			&ep->com.mapped_remote_addr;

		cc = snprintf(epd->buf + epd->pos, space,
			      "ep %p cm_id %p qp %p state %d flags 0x%lx "
			      "history 0x%lx hwtid %d atid %d "
			      "conn_na %u abort_na %u "
			      "%pI6:%d/%d <-> %pI6:%d/%d\n",
			      ep, ep->com.cm_id, ep->com.qp,
			      (int)ep->com.state, ep->com.flags,
			      ep->com.history, ep->hwtid, ep->atid,
			      ep->stats.connect_neg_adv,
			      ep->stats.abort_neg_adv,
			      &lsin6->sin6_addr, ntohs(lsin6->sin6_port),
			      ntohs(mapped_lsin6->sin6_port),
			      &rsin6->sin6_addr, ntohs(rsin6->sin6_port),
			      ntohs(mapped_rsin6->sin6_port));
	}
	if (cc < space)
		epd->pos += cc;
	return 0;
}
