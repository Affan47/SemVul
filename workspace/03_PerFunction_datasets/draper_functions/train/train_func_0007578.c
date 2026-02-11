message_packet_log(struct message *msg)
{
#if defined (USE_DEBUG)
	struct sockaddr *src, *dst;
	struct transport *t = msg->transport;


	if (msg->xmits > 0)
		return;

#if defined (USE_NAT_TRAVERSAL)
	if (msg->exchange && msg->exchange->flags & EXCHANGE_FLAG_NAT_T_ENABLE)
		t = ((struct virtual_transport *)msg->transport)->encap;
#endif


	if (msg->exchange &&
	    msg->exchange->initiator ^ (msg->exchange->step % 2)) {
		t->vtbl->get_src(t, &src);
		t->vtbl->get_dst(t, &dst);
	} else {
		t->vtbl->get_src(t, &dst);
		t->vtbl->get_dst(t, &src);
	}

	log_packet_iov(src, dst, msg->iov, msg->iovlen);
#endif
}
