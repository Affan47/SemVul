scc_socket_modem_write(int port, int c, double dcycs)
{
	Scc	*scc_ptr;
	char	*str;
	word32	modem_mode;
	int	do_echo;
	int	got_at;
	int	len;

	scc_ptr = &(scc_stat[port]);

	if(scc_ptr->sockfd == -1) {
		scc_ptr->socket_state = 0;
		scc_socket_maybe_open_incoming(port, dcycs);
	}

	modem_mode = scc_ptr->modem_mode;
	str = &(scc_ptr->modem_cmd_str[0]);

#if 0
	printf("M: %02x\n", c);
#endif
	do_echo = ((modem_mode & SCCMODEM_NOECHO) == 0);
	len = scc_ptr->modem_cmd_len;
	got_at = 0;
	if(len >= 2 && str[0] == 'a' && str[1] == 't') {

		got_at = 1;
	}
	if(c == 0x0d) {
		if(do_echo) {
			scc_add_to_readbuf(port, c, dcycs);
			scc_add_to_readbuf(port, 0x0a, dcycs);
		}
		do_echo = 0;
		scc_socket_do_cmd_str(port, dcycs);
		scc_ptr->modem_cmd_len = 0;
		len = 0;
		str[0] = 0;
	} else if(c == 0x08) {
		if(len <= 0) {
			do_echo = 0;
		} else if(len == 2 && got_at) {
			do_echo = 0;
		} else {

			len--;
			str[len] = 0;
		}
	} else if(c < 0x20) {


		do_echo = 0;
	} else {

		if(len < SCC_MODEM_MAX_CMD_STR) {
			str[len] = tolower(c);
			str[len+1] = 0;
			len++;
		}
	}
	scc_ptr->modem_cmd_len = len;
	if(do_echo) {
		scc_add_to_readbuf(port, c, dcycs);
	}
}
