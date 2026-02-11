create_connection(char *dst, bdaddr_t *bdaddr)
{
	struct l2cap_options l2o;
	struct sockaddr_l2 l2a;
	socklen_t olen;
	int sk, r = 0;
	struct script_arg down_cmd;

	syslog(LOG_INFO, "Connecting to %s", dst);

	sk = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
	if (sk < 0) {
		syslog(LOG_ERR, "Cannot create L2CAP socket. %s(%d)",
						strerror(errno), errno);
		return -1;
	}


	memset(&l2o, 0, sizeof(l2o));
	olen = sizeof(l2o);
	getsockopt(sk, SOL_L2CAP, L2CAP_OPTIONS, &l2o, &olen);
	l2o.imtu = l2o.omtu = BNEP_MTU;
	setsockopt(sk, SOL_L2CAP, L2CAP_OPTIONS, &l2o, sizeof(l2o));

	memset(&l2a, 0, sizeof(l2a));
	l2a.l2_family = AF_BLUETOOTH;
	bacpy(&l2a.l2_bdaddr, &src_addr);

	if (bind(sk, (struct sockaddr *) &l2a, sizeof(l2a)))
		syslog(LOG_ERR, "Bind failed. %s(%d)",
						strerror(errno), errno);

	memset(&l2a, 0, sizeof(l2a));
	l2a.l2_family = AF_BLUETOOTH;
	bacpy(&l2a.l2_bdaddr, bdaddr);
	l2a.l2_psm = htobs(BNEP_PSM);

	if (!connect(sk, (struct sockaddr *) &l2a, sizeof(l2a)) &&
			!bnep_create_connection(sk, role, service, netdev)) {

		syslog(LOG_INFO, "%s connected", netdev);

		run_script(devupcmd, netdev, dst, sk, -1);

		if (persist || devdowncmd) {
				memset(&down_cmd, 0, sizeof(struct script_arg));
				strncpy(down_cmd.dev, netdev, strlen(netdev) + 1);
				strncpy(down_cmd.dst, dst, strlen(dst) + 1);
				down_cmd.sk = sk;
				down_cmd.nsk = -1;
				w4_hup(sk, &down_cmd);

			if (terminate && cleanup) {
				syslog(LOG_INFO, "Disconnecting from %s.", dst);
				do_kill(dst);
			}
		}

		r = 0;
	} else {
		syslog(LOG_ERR, "Connect to %s failed. %s(%d)",
						dst, strerror(errno), errno);
		r = 1;
	}

	close(sk);

	if (use_cache) {
		if (!r) {

			strcpy(cache.dst, dst);
			bacpy(&cache.bdaddr, bdaddr);
			cache.valid = use_cache;
		} else
			cache.valid--;
	}

	return r;
}
