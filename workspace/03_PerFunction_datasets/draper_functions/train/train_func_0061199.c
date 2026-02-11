o2net_send_status_magic(struct socket *sock, struct o2net_msg *hdr,
				   enum o2net_system_error syserr, int err)
{
	struct kvec vec = {
		.iov_base = hdr,
		.iov_len = sizeof(struct o2net_msg),
	};

	BUG_ON(syserr >= O2NET_ERR_MAX);


	hdr->sys_status = cpu_to_be32(syserr);
	hdr->status = cpu_to_be32(err);
	hdr->magic = cpu_to_be16(O2NET_MSG_STATUS_MAGIC);
	hdr->data_len = 0;

	msglog(hdr, "about to send status magic %d\n", err);

	return o2net_send_tcp_msg(sock, &vec, 1, sizeof(struct o2net_msg));
}
