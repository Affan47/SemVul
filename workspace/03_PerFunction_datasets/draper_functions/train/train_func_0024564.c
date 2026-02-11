apparmor_socket_sendmsg(struct socket *sock,
				   struct msghdr *msg, int size)
{
	int error = aa_sock_msg_perm(OP_SENDMSG, AA_MAY_SEND, sock, msg, size);
	if (!error) {


		;
	}

	return error;
}
