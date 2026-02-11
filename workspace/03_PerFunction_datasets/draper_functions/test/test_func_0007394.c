cli_proxy_cmd(int *sock_in, int *sock_out) {
	int ret;

	fill_passwd(cli_opts.own_user);

	ret = spawn_command(exec_proxy_cmd, cli_opts.proxycmd,
			sock_out, sock_in, NULL, NULL);
	if (ret == DROPBEAR_FAILURE) {
		dropbear_exit("Failed running proxy command");
		*sock_in = *sock_out = -1;
	}
}
