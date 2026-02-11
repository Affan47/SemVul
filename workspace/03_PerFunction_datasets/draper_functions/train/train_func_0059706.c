ipsec_get_spi(size_t *sz, u_int8_t proto, struct message *msg)
{
	struct sockaddr *dst, *src;
	struct transport *transport = msg->transport;

	if (msg->exchange->phase == 1) {
		*sz = 0;
		return 0;
	} else {

		transport->vtbl->get_src(transport, &dst);

		transport->vtbl->get_dst(transport, &src);
		return sysdep_ipsec_get_spi(sz, proto, src, dst,
		    msg->exchange->seq);
	}
}
