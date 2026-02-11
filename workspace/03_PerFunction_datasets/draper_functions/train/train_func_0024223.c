stun_close_sock(void)
{
	if (0 <= args.stun_sock) {
		close(args.stun_sock);
		args.stun_sock = -1;
	}
}
