udp_encap_handle_message(struct transport *t)
{
	struct udp_transport	*u = (struct udp_transport *)t;
	struct sockaddr_storage	 from;
	struct message		*msg;
	u_int32_t	len = sizeof from;
	ssize_t		n;
	u_int8_t	buf[UDP_SIZE];

	n = recvfrom(u->s, buf, UDP_SIZE, 0, (struct sockaddr *)&from, &len);
	if (n == -1) {
		log_error("recvfrom (%d, %p, %d, %d, %p, %p)", u->s, buf,
		    UDP_SIZE, 0, &from, &len);
		return;
	}


	t = t->virtual->vtbl->clone(t->virtual, (struct sockaddr *)&from);
	if (!t)
		return;


	if (n < (ssize_t)sizeof(u_int32_t) || *(u_int32_t *)buf != 0) {

		log_print("udp_encap_handle_message: "
		    "Null-ESP marker not NULL or short message");
		return;
	}


	n -= sizeof(u_int32_t);
	if (n == 1 && buf[sizeof(u_int32_t)] == 0xFF)
		return;

	msg = message_alloc(t, buf + sizeof (u_int32_t), n);
	if (!msg) {
		log_error("failed to allocate message structure, dropping "
		    "packet received on transport %p", u);
		return;
	}
	message_recv(msg);
}
